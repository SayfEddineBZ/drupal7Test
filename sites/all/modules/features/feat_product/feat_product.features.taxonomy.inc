<?php
/**
 * @file
 * feat_product.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function feat_product_taxonomy_default_vocabularies() {
  return array(
    'type_de_produit' => array(
      'name' => 'type de produit',
      'machine_name' => 'type_de_produit',
      'description' => 'Taxo type de produit',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
