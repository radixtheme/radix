// Include gulp.
var gulp = require('gulp');

// Include plugins.
var scsslint = require('gulp-scss-lint');
var jshint = require('gulp-jshint');

// SCSS Linting.
gulp.task('scss-lint', function() {
  return gulp.src(['./assets/scss/**/*.scss'])
    .pipe(scsslint())
    .pipe(scsslint.failReporter());
});

// JS Linting.
gulp.task('js-lint', function() {
  return gulp.src('./assets/js/*.js')
    .pipe(jshint())
    .pipe(jshint.reporter('default'));
});

// Default Task
gulp.task('default', ['js-lint', 'scss-lint']);
