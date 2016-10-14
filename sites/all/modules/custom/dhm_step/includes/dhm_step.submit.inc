<?php

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 * @file 
 * Handles the form submission of the customer survey form
 */

/**
 * Handles what to do with the submitted form depending on what stage has been
 * completed.
 * 
 * @see dhm_step_form()
 * @see dhm_step_form_validate()
 * 
 * @param type $form
 * @param type $form_state 
 */
function dhm_step_form_submit($form, &$form_state) {

    switch ($form_state['stage']) {

        case 'personal_details':
            $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
            if ($form_state['triggering_element']['#value'] != 'Back') {
                dhm_step_personal_details_submit($form, $form_state);
                $form_state['complete'] = TRUE;
            }
            break;

        default:
            $form_state['multistep_values'][$form_state['stage']] = $form_state['values'];
            $form_state['new_stage'] = dhm_step_move_to_next_stage($form, $form_state);
            break;
    }
    if (isset($form_state['complete']))
        drupal_goto('complete-page');

    if ($form_state['triggering_element']['#value'] == 'Back') {
        $form_state['new_stage'] = dhm_step_move_to_previous_stage($form, $form_state);
    }

    if (isset($form_state['multistep_values']['form_build_id'])) {
        $form_state['values']['form_build_id'] = $form_state['multistep_values']['form_build_id'];
    }
    $form_state['multistep_values']['form_build_id'] = $form_state['values']['form_build_id'];
    $form_state['stage'] = $form_state['new_stage'];
    $form_state['rebuild'] = TRUE;
}

/**
 * Handles the submission of the final stage
 * 
 * Sends an email to the user confirming their entry
 * 
 * @param type $form
 * @param type $form_state 
 */
function dhm_step_personal_details_submit($form, &$form_state) {

    $multstep_values = $form_state['multistep_values'];

    $module = 'dhm_step';
    $key = 'dhm_step_complete';
    $to = $multstep_values['personal_details']['email'] . '; ' . variable_get('site_mail', 'seifeddine.bouzidi@dhm-it.com');
    $from = variable_get('site_mail', 'seifeddine.bouzidi@dhm-it.com');
    $params = array(
        'body' => 'Thank you for filling in our survey. You have now been entered into our prize draw.',
        'subject' => 'Thank you for filling in our survey, ' . $multstep_values['personal_details']['name'],
    );
   
    $language = language_default();
    $send = TRUE;
    $result = drupal_mail($module, $key, $to, $language, $params, $from, $send);
    if ($result['result'] == TRUE) {
        
        drupal_set_message(t('Your message has been sent.').l("PDF", fillpdf_pdf_link($form_id = 1, $node_id = 1)).print_r($form));
    } else {
        drupal_set_message(t('There was a problem sending your message and it was not sent.'), 'error');
    }
   
}

/**
 * Returns what to show on the completion page.
 * 
 * @return type 
 */
function dhm_step_complete() {

    return 'Thank you for completing our survey. You have been sent an email confirming you\'ve been entered into our prize draw';
}
