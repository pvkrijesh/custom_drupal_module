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
  
function revenue_edit($form, $form_state,$revenue_id = NULL) {
    $obj = new RevenueService();
    $obj_data = $obj->fetchRevenue($revenue_id);
    if (!empty($revenue_id)) {
      $form['daily_entry_seq_id'] = array(
	'#type' => 'hidden',
	'#value' => isset($revenue_id)?$revenue_id:'',
      );
  }

    $format = 'd-m-Y';
    $form['created_date'] = array(
      '#type' => 'date_popup',
      '#date_format'=>$format,
      '#title' => t('Revenue Date'),
      '#size' => 20,
      '#maxlength' => 20,
      '#default_value'=>$obj->fetch_date($revenue_id),
      '#disabled'=>TRUE,
      '#date_label_position' => 'none', 
      );
    
    
    $form['bus_sch_seq_id'] = array(
      '#title' => 'Form IV Unique',
      '#type' => 'textfield', 
      '#required' => TRUE,
      '#autocomplete_path' => 'revenue/autocomplete',
      '#default_value' => $obj_data->getbus_sch_seq_id(),
      '#disabled' => TRUE,
    );

    $dropdown_array=array('1'=>'Morning','2'=>'Night');
    $form['split_seq_id'] = array(
      '#title' => 'Shift',
      '#type' => 'select',
      '#options' => $dropdown_array,
      '#id' => 'Shiftid',
    );

    $form['sch_det_type_seq_id'] = array(
      '#title' => 'Schedules',
      '#type' => 'checkbox',
      '#description' => t('Check if the trip Cancelled'),
      '#default_value' =>$obj->fetchShift($revenue_id),
    );

    $form['total_revenue'] = array(
      '#type' => t('textfield'),
      '#title' => t("Revenue"),
      '#default_value' => $obj_data->gettotal_revenue(),
      '#rules' => array('chars[0,1,2,3,4,5,6,7,8,9,.]'),
      '#states' => array(
	  "visible" => array(
	      "input[name='sch_det_type_seq_id']" => array("checked" => FALSE)),
	    ),
    );
    
    $form['total_kms'] = array(
      '#type' => t('textfield'),
      '#title' => t("Kilometers"),
      '#default_value' => $obj_data->gettotal_kms(),
      '#rules' => array('chars[0,1,2,3,4,5,6,7,8,9,.]'),
      '#states' => array(
	  "visible" => array(
	    "input[name='sch_det_type_seq_id']" => array("checked" => FALSE)),
	  ),	
    );  
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Save'
    );
  return $form;
}  
	