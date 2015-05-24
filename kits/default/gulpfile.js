// Include gulp
var gulp = require('gulp');
var browserSync = require('browser-sync').create();

// Include Our Plugins
var sass = require('gulp-sass');
var rename = require('gulp-rename');
var compass = require('gulp-compass');
var imagemin = require('gulp-imagemin');
var pngcrush = require('imagemin-pngcrush');
var livereload = require('gulp-livereload');
var shell = require('gulp-shell')

// Compress images
gulp.task('images', function () {
  return gulp.src('assets/images/**/*')
    .pipe(imagemin({
      progressive: true,
      svgoPlugins: [{ removeViewBox: false }],
      use: [pngcrush()]
    }))
    .pipe(gulp.dest('assets/images'));
});

// Static Server + watching scss files
gulp.task('serve', ['sass'], function() {
  browserSync.init({
    proxy: "192.168.56.144"
  })

  gulp.watch('assets/sass/**/*.scss', ['sass']);
  gulp.watch('assets/stylesheets/**/*').on('change', browserSync.reload);
});

// Compile Our Sass with Bundle[d] Compass
gulp.task('sass', function() {
  return gulp.src('assets/sass/*.scss')
    .pipe(compass({
      config_file: 'config.rb',
      css: 'assets/stylesheets',
      sass: 'assets/sass',
      bundle_exec: true
    }))
    .pipe(gulp.dest('assets/stylesheets'));
});

// Run drush to clear the theme registry.
gulp.task('drush', shell.task([
  'drush cache-clear theme-registry'
]));

// Watch Files For Changes
//gulp.task('watch', function() {

//browserSync.reload();

// Watch php, inc and info file changes to run drush task.
//gulp.watch('**/*.{php, inc, info}', ['drush']);

// Start livereload and watch on css/js changes.
//var server = livereload();
//livereload.listen();
//gulp.watch('assets/stylesheets/*.css').on('change', livereload.changed);
//gulp.watch('assets/stylesheets/*.css').on('change', function(file) {
//  server.changed(file.path);
//});
//});

// Default Task
gulp.task('default', ['serve']);