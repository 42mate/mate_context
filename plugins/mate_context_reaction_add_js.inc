<?php
/**
 * @file
 * Context reaction RRK Add Javascript
 */

class mate_context_reaction_addjs extends context_reaction {
  
  function options_form($context) {
    
    $form = array();

    // Load the previously saved settings.
    $data = $this->fetch_from_context($context);
    if (!isset($data['js_page_scope'])) {
      $data['js_page_scope'] = 'footer';
    }
    if (!isset($data['add_js'])) {
      $data['add_js'] = '';
    }
    
    $form['js_page_scope'] = array(
      '#title' => t('Position on DOM page'),
      '#type' => 'select',
      '#options' => array(
        'header' => t('Header'),
        'footer' => t('Body'),
       ),
      '#default_value' => $data['js_page_scope'],
    );
    
    $form['from'] = array(
      '#type' => 'item',
      '#markup' => '<div class="row-info">
        <div class="info">' . t('Make sure to test the script to avoid Js errors on page. You can use an ' .
          '<a href="@url" target="_blank">online tool</a> to check syntax errors', array('@url' => url('http://jshint.com/'))) . 
        '</div>
      </div>',
    );
    
    $form['add_js'] = array(
      '#title' => t('Javascript code'),
      '#type' => 'textarea',
      '#rows' => '8',
      '#cols' => '60',
      '#default_value' => $data['add_js'],
    );
    
    return $form;
  }
  
  /**
   * Output Js scripts of active contexts.
   */
  function execute() {
    
    $contexts = context_active_contexts();    
    foreach ($contexts as $val_contxt) {
      if (!empty($val_contxt->reactions[$this->plugin])) {
        $js_script = $val_contxt->reactions[$this->plugin]['add_js'];
        if (isset($val_contxt->reactions[$this->plugin]['js_page_scope']) &&
          $val_contxt->reactions[$this->plugin]['js_page_scope'] == 'header') {
          $js_scope = $val_contxt->reactions[$this->plugin]['js_page_scope'];
        }
        else {
          $js_scope = 'footer';
        }
        drupal_add_js($js_script, array(
          'type' => 'inline', 
          'group' => JS_LIBRARY, 
          'scope' => $js_scope,
          'weight' => '-400',
        ));
      }
    }
  }
}
