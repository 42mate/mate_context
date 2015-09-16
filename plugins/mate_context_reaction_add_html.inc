<?php
/**
 * @file
 * Context reaction RRK Add HTML
 */

class mate_context_reaction_add_html extends context_reaction {
  
  function options_form($context) {
    
    $form = array();

    // Load the previously saved settings.
    $data = $this->fetch_from_context($context);
    
    $form['page_scope_snippet'] = array(
      '#title' => t('Position on DOM page'),
      '#type' => 'select',
      '#options' => array(
        'page_top' => t('Page top area'),
        'content' => t('Content area'),
        'page_bottom' => t('Page bottom area'),
       ),
      '#default_value' => $data['page_scope_snippet'],
      '#description' => t('Determines area to add the snippet.'),
    );
    $form['weight_snippet'] = array(
      '#type' => 'textfield',
      '#title' => t('Weight'),
      '#default_value' => (empty($data['weight_snippet']) ? '0' : $data['weight_snippet']),
      '#maxlength' => 255,
      '#size' => 4,
      '#description' => t('Determines the relative position of snippet on page, higher-weighted items sinks.'),
    );
    $form['help'] = array(
      '#type' => 'item',
      '#markup' => '<div class="row-info">
        <div class="info">' . t('Make sure to validate the HTML snippet to avoid markup errors on the page:') .
          '<ul>' .
          '<li>' . t('To validate html, please use <a href="!htmlvalidatorurl" target="_blank">W3C Markup validation tool</a>', 
            array('!htmlvalidatorurl' => url('https://validator.w3.org/#validate_by_input'))) . '</li>' .
          '<li>' . t('If the snippet has Javascript, please use <a href="!jsvalidatorurl" target="_blank">JsHint</a>', 
            array('!jsvalidatorurl' => url('http://jshint.com'))) . '</li>' .
        '</ul></div></div>',
    );
    $form['html_snippet'] = array(
      '#title' => t('HTML snippet'),
      '#type' => 'textarea',
      '#rows' => '8',
      '#cols' => '60',
      '#default_value' => (empty($data['html_snippet']) ? '' : $data['html_snippet']),
      '#description' => t('HTML snippet to add on page (like Fb/Twitter tracking pixels, Google Adwords,...).'),
    );
    
    return $form;
  }
  
  /**
   * Output HTML snippet on active contexts.
   */
  function execute(&$page) {
    
    $contexts = context_active_contexts();
    $plugin_index = 0;
    foreach ($contexts as $val_contxt) {
      if (!empty($val_contxt->reactions[$this->plugin])) {
        
        $context_page_instance = $this->plugin . '_' . $plugin_index;
        $page[$val_contxt->reactions[$this->plugin]['page_scope_snippet']][$context_page_instance] = array(
          '#weight' => $val_contxt->reactions[$this->plugin]['weight_snippet'], 
          '#markup' => $val_contxt->reactions[$this->plugin]['html_snippet'],
        );
        $plugin_index++;
      }
    }
  }
  
}
