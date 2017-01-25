<?php
/**
 * @file
 * Batch Callback batch callback
 */

/**
 * Batch callback function
 *
 * @return mixed
 */
function batch_callback_run_batch_process() {

  //grab global setting example
  $some_global_setting = variable_get('batch_callback_some_global_setting', '');

  $form['heading'] = array(
    '#type' => 'markup',
    '#markup' => t('This will run the user profile to civicrm name update process.'),
    '#prefix' => '<p>',
    '#suffix' => '</p>',
  );

  $form['some_value'] = array(
    '#type' => 'textfield',
    '#title' => 'some value',
    '#description' => 'Some value you want to use in processing.'
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Run batch process'),
  );
  return $form;

}

/**
 * Submit callback for run process page
 *
 * Here you prepare your variables and setup the batch, passing what you need to the callback
 *
 * @param $form
 * @param $form_state
 */
function batch_callback_run_batch_process_submit($form, $form_state) {
  //grab global setting example
  $some_global_setting = variable_get('batch_callback_some_global_setting', '');

  // gather up your things to get processed
  // in this case all uids
  $user_query = new EntityFieldQuery();
  $user_result = $user_query->entityCondition('entity_type', 'user')
    ->execute();

  // the values from the batch start form
  $form_values = $form_state['values'];

  // setup array of operations
  $operations = array();
  if(!empty($user_result['user'])) {

    foreach (array_keys($user_result['user']) as $uid) {
      $operations[] = array('_batch_callback_batch_process_callback', array($form_values, $uid));
    }

    // setup batch
    $batch = array(
      'operations' => $operations,
      'finished' => 'batch_callback_batch_process_finished',
    );
    batch_set($batch);
  }
}

/**
 * Function called by the batch api function to display results of batch run
 *
 * @param $success
 * @param $results
 * @param $operations
 */
function batch_callback_process_finished($success, $results, $operations) {
  if ($success) {
    // Here we could do something meaningful with the results.
    // We just display the number of nodes we processed...
    drupal_set_message(t('@count results', array('@count' => count($results))));
    // drupal_set_message(t('The final result was "%final"', array('%final' => end($results))));
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
  }

}

