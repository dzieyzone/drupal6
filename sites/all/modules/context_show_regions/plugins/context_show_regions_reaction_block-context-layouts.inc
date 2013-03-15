<?php
// $Id: context_reaction_block.inc,v 1.1.2.35 2010/08/06 16:13:32 jmiccolis Exp $

/**
 * Expose blocks as context reactions.
 */
class context_show_regions_reaction_block extends context_layouts_reaction_block{
  /**
   * Settings form for variables.
   */
  function settings_form() {
    $form = array();
    $form['context_reaction_block_disable_core'] = array(
      '#title' => t('Core block system'),
      '#type' => 'select',
      '#options' => array(
        FALSE => t('Enabled'),
        TRUE => t('Disabled'),
      ),
      '#default_value' => variable_get('context_reaction_block_disable_core', FALSE),
      '#description' => t('If enabled Context will include blocks enabled through the core block system when rendering regions. Disable to improve performance and hide the core block administration UI.')
    );
    return $form;
  }

  /**
  * An alternative version of block_list() that provides any context enabled blocks.
  */
  function block_list($region) {
    static $build_queue;
    static $build_contexts;
    static $context_blocks = array();
    static $empty_blocks = array();

    // Static cache a region => block array of blocks that should be built *if*
    // the given region is requested. Note that the blocks are not themselves
    // built in this first run as not all regions may be requested even if
    // active contexts include blocks in those regions.
    $contexts = context_active_contexts();
    if (!isset($build_queue) || $build_contexts != array_keys($contexts)) {
      $info = $this->get_blocks();
      $build_queue = array();
      $build_contexts = array_keys($contexts);
      foreach ($contexts as $context) {
        $options = $this->fetch_from_context($context);
        if (!empty($options['blocks'])) {
          foreach ($options['blocks'] as $block) {
            $block = (object) $block;
            $block->context = $context->name;
            $block->bid = "{$block->module}-{$block->delta}";
            $block->cache = isset($info[$block->bid]->cache) ? $info[$block->bid]->cache : BLOCK_NO_CACHE;
            $build_queue[$block->region][] = $block;
          }
        }
      }
    }

    // Context blocks.
    if (!isset($context_blocks[$region])) {
      $context_blocks[$region] = array();
      $empty_blocks[$region] = array();
      if (!empty($build_queue[$region])) {
        foreach ($build_queue[$region] as $block) {
          $block = $this->build_block($block);
          if (!empty($block->content)) {
            $context_blocks[$region][] = $block;
          }
          else {
            $empty_blocks[$region][] = $block;
          }
        }
      }
    }

    // Get core blocks only if enabled.
    $blocks = !variable_get('context_reaction_block_disable_core', FALSE) ? block_list($region) : array();
    $blocks = array_merge($blocks, $context_blocks[$region]);

    // Only include empty blocks if all regions should be shown or there are
    // non-empty blocks in the same region.
    //$all_regions = variable_get('context_reaction_block_all_regions', FALSE);
    $all_regions = $_SESSION['show_regions'];    
    if ($this->is_editable() && ($all_regions || !empty($blocks))) {
      $blocks = array_merge($blocks, $empty_blocks[$region]);
    }

    // Sort everything.
    uasort($blocks, array('context_reaction_block', 'block_sort'));
    return $blocks;
  }
  
}