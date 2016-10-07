<?php
/**
 * @file
 * feat_product.features.inc
 */

/**
 * Implements hook_views_api().
 */
function feat_product_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function feat_product_node_info() {
  $items = array(
    'produit' => array(
      'name' => t('Produit'),
      'base' => 'node_content',
      'description' => t('Type de contenu produit'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
