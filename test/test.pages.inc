<?php
function add_test($form, $form_state) {
	$form = array();
    $form['first_name'] = array(
      '#type' => 'textfield',
      '#title' => t('First Name'),
      '#size' => 20,
      '#maxlength' => 20,
      '#required' => TRUE
      );
	  
	$form['last_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Last Name'),
      '#size' => 20,
      '#maxlength' => 20,
      '#required' => TRUE
      );
	$form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save'
  );
    
	return $form;
	}
	
function add_test_submit($form_id, $form_values) {
$first_name = $form_values['input']['first_name'];
$last_name = $form_values['input']['last_name'];
$insert = db_insert('test')
    -> fields(array(
    'firstname' => $first_name,
    'lastname' => $last_name
))
->execute();  
  }	
  

  return $form;
}  
	