<?php
// $Id: views_slideshow_imageflow.variables.inc,v 1.1.2.4 2010/07/16 14:02:41 aaron Exp $

/**
 * @file Contains the variables and defaults used by Views Slideshow: ImageFlow.
 */

/**
 * The variable namespace for Views Slideshow: ImageFlow.
 */
define('VIEWS_SLIDESHOW_IMAGEFLOW_NAMESPACE', 'views_slideshow_imageflow__');

/**
 * Wrapper for variable_get() that uses the Views Slideshow: ImageFlow variable
 * registry.
 *
 * @param string $name
 *  The variable name to retrieve. Note that it will be namespaced by
 *  pre-pending VIEWS_SLIDESHOW_IMAGEFLOW_NAMESPACE, as to avoid variable
 *  collisions with other modules.
 * @param unknown $default
 *  An optional default variable to return if the variable hasn't been set
 *  yet. Note that within this module, all variables should already be set
 *  in the views_slideshow_imageflow_variable_default() function.
 * @return unknown
 *  Returns the stored variable or its default.
 *
 * @see views_slideshow_imageflow_variable_set()
 * @see views_slideshow_imageflow_variable_del()
 * @see views_slideshow_imageflow_variable_default()
 */
function views_slideshow_imageflow_variable_get($name, $default = NULL) {
  // Allow for an override of the default.
  // Useful when a variable is required (like $path), but namespacing still desired.
  if (!isset($default)) {
    $default = views_slideshow_imageflow_variable_default($name);
  }
  // Namespace all variables
  $variable_name = VIEWS_SLIDESHOW_IMAGEFLOW_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() for Views Slideshow: ImageFlow variable registry.
 *
 * @param string $name
 *  The variable name to set. Note that it will be namespaced by
 *  pre-pending VIEWS_SLIDESHOW_IMAGEFLOW_NAMESPACE, as to avoid variable
 *  collisions with other modules.
 * @param unknown $value
 *  The value for which to set the variable.
 * @return unknown
 *  Returns the stored variable after setting.
 *
 * @see views_slideshow_imageflow_variable_get()
 * @see views_slideshow_imageflow_variable_del()
 * @see views_slideshow_imageflow_variable_default()
 */
function views_slideshow_imageflow_variable_set($name, $value) {
  $variable_name = VIEWS_SLIDESHOW_IMAGEFLOW_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() for Views Slideshow: ImageFlow variable registry.
 *
 * @param string $name
 *  The variable name to delete. Note that it will be namespaced by
 *  pre-pending VIEWS_SLIDESHOW_IMAGEFLOW_NAMESPACE, as to avoid variable
 *  collisions with other modules.
 *
 * @see views_slideshow_imageflow_variable_get()
 * @see views_slideshow_imageflow_variable_set()
 * @see views_slideshow_imageflow_variable_default()
 */
function views_slideshow_imageflow_variable_del($name) {
  $variable_name = VIEWS_SLIDESHOW_IMAGEFLOW_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Views Slideshow: ImageFlow namespace.
 *
 * @param string $name
 *  Optional variable name to retrieve the default. Note that it has not yet
 *  been pre-pended with the VIEWS_SLIDESHOW_IMAGEFLOW_NAMESPACE namespace at
 *  this time.
 * @return unknown
 *  The default value of this variable, if it's been set, or NULL, unless
 *  $name is NULL, in which case we return an array of all default values.
 *
 * @see views_slideshow_imageflow_variable_get()
 * @see views_slideshow_imageflow_variable_set()
 * @see views_slideshow_imageflow_variable_del()
 */
function views_slideshow_imageflow_variable_default($name = NULL) {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      // Path to ImageFlow plugin.
      'plugin_path' => '',
      // Whether to use the packed versions of the script.
      'packed' => TRUE,
      // Whether to include the CSS file.
      'include_css' => TRUE,

      // Default view settings.
      'aspect_ratio' => '1.964',
      'images_height' => '0.67',
      'image_cursor' => 'pointer',
      'slider_cursor' => 'pointer',
      'slider' => TRUE,
      'start' => 'middle',
      'captions' => TRUE,
      'imageFocusM' => '1.0',
      'scrollbarP' => '0.6',
      'imageFocusMax' => '4',
      'onClick' => 'function() { document.location = this.url; }',
    );
  }

  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 *
 * @param string $name
 *  The variable name to retrieve the namespaced name.
 * @return string
 *  The fully namespace variable name, prepended with
 *  VIEWS_SLIDESHOW_IMAGEFLOW_NAMESPACE.
 */
function views_slideshow_imageflow_variable_name($name) {
  return VIEWS_SLIDESHOW_IMAGEFLOW_NAMESPACE . $name;
}
