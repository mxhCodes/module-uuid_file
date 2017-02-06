<?php
/**
 * @file
 * UUID File Stream wrapper class.
 */
class UuidFileStreamWrapper extends DrupalPublicStreamWrapper {
  /**
   * Overrides getExternalUrl().
   */
  function getExternalUrl() {
    $uri = $this->getUri();
    $file = uuid_file_by_uri($uri);
    
    if (!empty($file->uuid)) {
      $query = array();
      if (strpos($uri, '://styles/')) {
        // Obviously this is an image style uri.
        $target = file_uri_target($uri);
        $pieces = explode('/', $target);
        $query['style'] = $pieces[1];
      }
      $file_extension = uuid_file_extension_by_mime($file->filemime);
      return url('file-uuid/' . $file->uuid . '.' . $file_extension, array('absolute' => TRUE, 'query' => $query));
    }
    else {
      return parent::getExternalUrl();
    }
    
  }
}
