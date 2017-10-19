<?php
###############################################
#    Author : BITAM Salim
#    GITHUB : https://github.com/soolidsnake/
###############################################



function str_xor($str,$max_depth=0,$depth=0)
{
    $mid=strlen($str)/2;
    $left=substr($str,0,$mid);
    $right=substr($str,$mid);
    if ($depth<$max_depth)
    {
        $left=str_xor($left,$max_depth,$depth+1);
        $right=str_xor($right,$max_depth,$depth+1);
    }
    $out="";
    for ($i=0;$i<strlen($left);++$i)
        $out.=$left[$i]^$right[$i];
    return $out;
}


function hasher($string)
{
    if (!ctype_alnum($string))
        return null;
    $t=trim(shell_exec("echo -n '{$string}' | openssl dgst -whirlpool | openssl dgst -rmd160"));
    $t=str_replace("(stdin)= ","",$t); //some linux adds this
    if (!$t)
        return null;
    return bin2hex(str_xor(hex2bin($t),1));
}

$user='admin';



extract($_POST);

$i = 10000000;

while (true) 
{

    $hashed = hasher($i);

    if(substr($hashed, 0, 2) =="0e" &&  is_numeric(substr($hashed, 2, 10)))
        {
            echo "LINE = ".$i."\n";
            echo "HASHED = ".$hashed."\n";
            echo "GG\n";
        }

    $i += 1;        
}


?>
