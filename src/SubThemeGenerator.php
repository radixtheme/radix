<?php

declare(strict_types = 1);

namespace Drupal\radix;

use RuntimeException;
use Symfony\Component\Filesystem\Filesystem;
use Symfony\Component\Finder\Finder;

class SubThemeGenerator {

  /**
   * @var \Symfony\Component\Filesystem\Filesystem
   */
  protected $fs;

  /**
   * @var \Symfony\Component\Finder\Finder
   */
  protected $finder;

  /**
   * @var string
   */
  protected $machineNameOld = '';

  /**
   * @var string
   */
  protected $dir = '';

  public function getDir(): string {
    return $this->dir;
  }

  /**
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
   * @var string
   */
  protected $machineName = '';

  public function getMachineName(): string {
    if (!$this->machineName) {
      return basename($this->getDir());
    }

    return $this->machineName;
  }

  public function setMachineName(string $machineName) {
    $this->machineName = $machineName;

    return $this;
  }

  /**
   * @var string
   */
  protected $name = '';

  public function getName(): string {
    return $this->name;
  }

  /**
   * @return $this
   */
  public function setName(string $name) {
    $this->name = $name;

    return $this;
  }

  protected $description = '';

  public function getDescription(): string {
    return $this->description;
  }

  public function setDescription(string $description) {
    $this->description = $description;

    return $this;
  }

  public function __construct() {
    $this->fs = new Filesystem();
    $this->finder = new Finder();
  }

  /**
   * @return $this
   */
  public function generate() {
    return $this
      ->initMachineNameOld()
      ->modifyFileContents()
      ->renameFiles();
  }

  /**
   * @return $this
   */
  protected function initMachineNameOld() {
    $dstDir = $this->getDir();
    $infoFiles = glob("$dstDir/*.info.yml");

    $this->machineNameOld = basename(reset($infoFiles), '.info.yml');

    return $this;
  }

  /**
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
   * @return string[]
   */
  protected function getFileNamesToRename(): array {
    // Find all files within the theme that match *{KIT_NAME}*.
    return array_keys(iterator_to_array($this->finder->files()->name("*{$this->machineNameOld}*")->in($this->getDir())));
  }

  /**
   * @return string[]
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
   * @return string[]
   */
  function getFilesToMakeReplacements(): array {
    return array_keys(iterator_to_array($this->finder->files()->in($this->getDir())));
  }

  protected function fileGetContents(string $fileName): string {
    $content = file_get_contents($fileName);
    if ($content === FALSE) {
      throw new RuntimeException("Could not read file '$fileName'", 1);
    }

    return $content;
  }

}
