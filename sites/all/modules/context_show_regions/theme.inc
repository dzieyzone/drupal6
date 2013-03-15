<?php 
/**
 * Preprocessor for theme('context_block_editable_region').
 */
function template_preprocess_context_block_editable_region(&$vars) {
  if (!empty($vars['editable'])) {
    // Show when empty?
    $vars['show_always'] = variable_get('context_reaction_block_all_regions', FALSE);

    // Provide the user-friendly name of the region
    global $theme_key;
    $regions = system_region_list($theme_key);
    $vars['region_description'] = isset($regions[$vars['region']]) ? $regions[$vars['region']] : $vars['region'];
  }
}