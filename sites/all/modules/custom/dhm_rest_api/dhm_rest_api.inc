<?php
// dhm_rest_api.inc
/**
* Callback for creating produit services.
*
* @param object $data
* @return object
*/
function _dhm_rest_api_create($data) {
  global $user;

  unset($data->id);
  $data->uid = $user->uid;
  $data->created = time();
  $data->modified = time();

  if (!isset($data->subject)) {
    return services_error('Missing produit attribute subject', 406);
  }

  if (!isset($data->produit)) {
    return services_error('Missing produit attribute produit', 406);
  }

  dhm_rest_api_write_produit($data);
  
  return (object)array(
    'id' => $data->id,
    'uri' => services_service_uri(array('produit', $data->id)),
  );
}

// dhm_rest_api.inc
/**
* Callback for updating produit services.
*
* @param int $id
* @param object $data
* @return object
*/
function _dhm_rest_api_update($id, $data) {
  global $user;
  $produit = dhm_rest_api_get_produit($id);

  unset($data->created);
  $data->id = $id;
  $data->uid = $produit->uid;
  $data->modified = time();

  dhm_rest_api_write_produit($data);
  
  return (object)array(
    'id' => $id,
    'uri' => services_service_uri(array('produit', $id)),
  );
} 
/**
* Callback for retrieving produit services.
*
* @param int $id
* @return object
*/
function _dhm_rest_api_retrieve($id) {
  return dhm_rest_api_get_produit($id);
}

/**
* Callback for deleting produit services.
*
* @param int $id
* @return object
*/
function _dhm_rest_api_delete($id) {
  dhm_rest_api_delete_produit($id);
  
  return (object)array(
    'id' => $id,
  );
}

function _dhm_rest_api_index($page, $parameters) {
  global $user;

  $produits = array();
  $res = db_query("SELECT * FROM {produit} 
WHERE uid='".$user->uid."'ORDER BY modified DESC");
  foreach ($res as $produit) {
    $produits[] = $produit;
  }

  return $produits;
}

/**
* Access callback for the produit service.
*
* @param string $op
*  The operation that's going to be performed.
* @param array $args
*  The arguments that will be passed to the callback.
* @return bool
*  Whether access is given or not.
*/

function _dhm_rest_api_access($op, $args) {
  global $user;
  $access = FALSE;

  switch ($op) {
    case 'view':
      $produit = dhm_rest_api_get_produit($args[0]);
      $access = user_access('produit service view any produit');
      $access = $access || $produit->uid == $user->uid && 
      user_access('produit service view own produits');
      break;
    case 'update':
      $produit = dhm_rest_api_get_produit($args[0]->id);
      $access = user_access('produit service edit any produit');
      $access = $access || $produit->uid == $user->uid &&  
      user_access('produit service edit own produits');
      break;
    case 'delete':
      $produit = dhm_rest_api_get_produit($args[0]);
      $access = user_access('produit service delete any produit');
      $access = $access || $produit->uid == $user->uid && 
      user_access('produit service delete own produits');
      break;
  }
  $access = TRUE;
  
  return $access;
}
?>