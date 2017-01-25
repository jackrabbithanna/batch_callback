<?php
/**
 * @file
 * Batch Callback settings form callbacks
 */

/**
 * Settings form callback function
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function batch_callback_settings_form($form, &$form_state) {
  $form['heading'] = array(
    '#type' => 'markup',
    '#markup' => '<p>General or global settings will be made here</p>',
  );

  $form['batch_callback_some_global_setting'] = array(
    '#type' => 'textfield',
    '#title' => 'Some Global Setting',
    '#description' => 'Some setting to pass to the batch run form.',
    '#default_value' =>  variable_get('batch_callback_some_global_setting', ''),
  );

  $form['#validate'][] = 'batch_callback_settings_form_validate';
  return system_settings_form($form);
}

/**
 * Settings form validation callback
 * @param $form
 * @param $form_state
 */
function batch_callback_settings_form_validate($form, &$form_state) {

}