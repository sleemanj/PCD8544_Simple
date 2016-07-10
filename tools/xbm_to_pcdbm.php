<?php
  // Convert an XBM format image into something you can pass to lcd.drawBitmap
  // You can convert to xbm using imagmagick ( convert [any image] [output.xbm] )  
  //
  // Included here just for reference, 
  //
  // Rather than installing PHP to do this, you can use this tool online here: 
  //    http://sparks.gogo.co.nz/pcd8554-bmp.html
  // (with jpg/gif/png/bmp and xbm format supported for input files)
  
  function xbm_to_pcdbm($f)
  {
    $Width       = 0;
    $Height      = 0;
    $BytesPerRow = 0;
    $PixNum      = 0;
    $ByteNum     = 0;
    $Out         = NULL;
    
    $lines = file($f);
    foreach($lines as $line)
    {
      if(preg_match('/#define .*width ([0-9]+)/', $line, $M))
      {
        $Width = $M[1];
        $BytesPerRow = ceil($Width/8);
      }
      elseif(preg_match('/#define .*height ([0-9]+)/', $line, $M))
      {
        $Height = $M[1];
      }
      elseif(preg_match('/0x/', $line))
      {
        if(!isset($Out))
        {
          $Out = array();
          for($y = 0; $y < ceil($Height/8); $y++)
          {
            $Out[$y] = array();
            for($x = 0; $x < $Width; $x++)
            {
              $Out[$y][$x]=0;
            }
          }
          
          $y = 0;
          $x = 0;
        }
      
        $bytes = preg_split('/,/', preg_replace('/\s/', '', $line));
        foreach($bytes as $byte)
        {
          if(!preg_match('/^0x/', $byte)) continue;
          
          // Moved to next row yet (rows are byte boundaries in xbm)
          if(floor($ByteNum++ / $BytesPerRow) != $y)
          {
            $y++;
            $x = 0;
          }
          
          $byte = hexdec(preg_replace('/^0x/', '', $byte));
          for($b = 0; $b < 8; $b++)
          {
            if($x < $Width) // xbm has trailing pixels in rows (each row is always a byte boundary)
            {
              $bit = ($byte & (1<<$b)) ? 1 : 0;
              $Out[$y/8][$x] |= ($bit << $y%8);
            }
            
            $x++;
          }
        }
      }
    }  
    
    return array($Width,$Height,$Out);
  }
  
  
  $Input = '/tmp/test.xbm';
    
  list($Width, $Height, $Output) = xbm_to_pcdbm($Input);
  
  $Name = preg_replace('/[^a-z0-9_]/', '', preg_replace('/\..*$/', '', basename($Input)));
  echo "const uint8_t {$Name}_Width    = {$Width};\n";
  echo "const uint8_t {$Name}_Height   = {$Height};\n";
  echo "const uint8_t PROGMEM {$Name}_Bitmap[] = { \n";
    foreach($Output as $i => $Bank)
    {
      echo "  ";
      foreach($Bank as $j => $Column)
      {        
        echo '0x'.str_pad(dechex($Column), 2, '0', STR_PAD_LEFT);
        if(!($i == count($Output)-1 && $j == count($Bank)-1))
         echo ', ';
      }
      echo "\n";
    }
  echo "};\n"
  
?>