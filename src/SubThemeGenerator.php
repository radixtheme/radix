<?php

declare(strict_types = 1);

namespace Drupal\radix;

use Symfony\Component\Filesystem\Filesystem;
use Symfony\Component\Finder\Finder;

/**
 * Class SubThemeGenerator. Generate radix subtheme.
 */
class SubThemeGenerator {

  /**
   * {@inheritdoc}
   *
   * @var \Symfony\Component\Filesystem\Filesystem
   */
  protected $fs;

  /**
   * {@inheritdoc}
   *
   * @var \Symfony\Component\Finder\Finder
   */
  protected $finder;

  /**
   * {@inheritdoc}
   *
   * @var string
   */
  protected $machineNameOld = '';

  /**
   * {@inheritdoc}
   *
   * @var string
   */
  protected $dir = '';

  /**
   * {@inheritdoc}
   */
  public function getDir(): string {
    return $this->dir;
  }

  /**
   * {@inheritdoc}
   *
   * @param string $dir
   *   Directory where a Radix starter kit already copied to.
   *
   * @return $this
   */
  public function setDir(string $dir) {
    $this->dir = $dir;

    return $this;
  }

  /**
   * {@inheritdoc}
   *
   * @var string
   */
  protected $machineName = '';

  /**
   * {@inheritdoc}
   */
  public function getMachineName(): string {
    if (!$this->machineName) {
      return basename($this->getDir());
    }

    return $this->machineName;
  }

  /**
   * {@inheritdoc}
   */
  public function setMachineName(string $machineName) {
    $this->machineName = $machineName;

    return $this;
  }

  /**
   * {@inheritdoc}
   *
   * @var string
   */
  protected $name = '';

  /**
   * {@inheritdoc}
   */
  public function getName(): string {
    return $this->name;
  }

  /**
   * {@inheritdoc}
   *
   * @return $this
   */
  public function setName(string $name) {
    $this->name = $name;

    return $this;
  }

  /**
   * {@inheritdoc}
   */
  protected $description = '';

  /**
   * {@inheritdoc}
   */
  public function getDescription(): string {
    return $this->description;
  }

  /**
   * {@inheritdoc}
   */
  public function setDescription(string $description) {
    $this->description = $description;

    return $this;
  }

  /**
   * {@inheritdoc}
   */
  public function __construct() {
    $this->fs = new Filesystem();
    $this->finder = new Finder();
  }

  /**
   * {@inheritdoc}
   *
   * @return $this
   */
  public function generate() {
    return $this
      ->initMachineNameOld()
      ->modifyFileContents()
      ->renameFiles();
  }

  /**
   * {@inheritdoc}
   *
   * @return $this
   */
  protected function initMachineNameOld() {
    $dstDir = $this->getDir();
    $infoFiles = glob("$dstDir/*.info.yml");

    $this->machineNameOld = basename(reset($infoFiles), '.info.yml');

    return $this;
  }

  /**
   * {@inheritdoc}
   *
   * @return $this
   */
  protected function modifyFileContents() {
    $replacementPairs = $this->getFileContentReplacementPairs();
    foreach ($this->getFilesToMakeReplacements() as $fileName) {
      $this->modifyFileContent($fileName, $replacementPairs);
    }

    return $this;
  }

  /**
   * {@inheritdoc}
   *
   * @return $this
   */
  protected function renameFiles() {
    $machineNameNew = $this->getMachineName();
    if ($this->machineNameOld === $machineNameNew) {
      return $this;
    }

    foreach ($this->getFileNamesToRename() as $fileName) {
      $this->fs->rename($fileName, str_replace($this->machineNameOld, $machineNameNew, $fileName));
    }

    return $this;
  }

  /**
   * {@inheritdoc}
   *
   * @return $this
   */
  protected function modifyFileContent(string $fileName, array $replacementPairs) {
    if (!$this->fs->exists($fileName)) {
      return $this;
    }

    $this->fs->dumpFile(
      $fileName,
      strtr($this->fileGetContents($fileName), $replacementPairs)
    );

    return $this;
  }

  /**
   * {@inheritdoc}
   *
   * @return string[]
   *   Returns file names.
   */
  protected function getFileNamesToRename(): array {
    // Find all files within the theme that match *{KIT_NAME}*.
    return array_keys(iterator_to_array($this->finder->files()->name("*{$this->machineNameOld}*")->in($this->getDir())));
  }

  /**
   * {@inheritdoc}
   *
   * @return string[]
   *   Returns replacement pairs.
   */
  protected function getFileContentReplacementPairs(): array {
    return [
      'RADIX_SUBTHEME_NAME' => $this->getName(),
      'RADIX_SUBTHEME_DESCRIPTION' => $this->getDescription(),
      'RADIX_SUBTHEME_MACHINE_NAME' => $this->getMachineName(),
      "\nhidden: true\n" => "\n",
    ];
  }

  /**
   * {@inheritdoc}
   *
   * @return string[]
   *   Returns files to make replacements.
   */
  public function getFilesToMakeReplacements(): array {
    return array_keys(iterator_to_array($this->finder->files()->in($this->getDir())));
  }

  /**
   * {@inheritdoc}
   */
  protected function fileGetContents(string $fileName): string {
    $content = file_get_contents($fileName);
    if ($content === FALSE) {
      throw new \RuntimeException("Could not read file '$fileName'", 1);
    }

    return $content;
  }

}
