<?php
function getstdinline(){
	$text=fgets(STDIN);
	$text=substr($text,0,-2);
	return $text;
}
function getfoldername($text){
	if($text[0]=="\"")$text=substr($text,1,-1);
	if($text[strlen($text)-1]=="\\")$text=substr($text,0,-1);
	return $text;
}
fwrite(STDOUT, "Main output folder: ");
$folder=getstdinline();
$folder=getfoldername($folder);
system("md \"".$folder."\"");
while(true){
	fwrite(STDOUT, "Sub output folder (question name): ");
	$name=getstdinline();
	$subfolder=$folder."\\".$name;
	system("md \"".$subfolder."\"");
	fwrite(STDOUT, "-----".$name."-----\n");
	system("md \"".$subfolder."\\http\"");
	fwrite(STDOUT, "question file: ");
	$input=getstdinline();
	echo "copy \"".$input."\" \"".$subfolder."\\http\\\"";
	system("copy \"".$input."\" \"".$subfolder."\\http\\cont.".pathinfo($input, PATHINFO_EXTENSION)."\"");
	fwrite(STDOUT, "timelimit: ");
	$input=getstdinline();
	$timelimit=(int)$input;
	fwrite(STDOUT, "memlimit: ");
	$input=getstdinline();
	$memlimit=(int)$input;
	fwrite(STDOUT, "testdata folder: ");
	$testdatafolder=getstdinline();
	$testdatafolder=getfoldername($testdatafolder);
	$testdatalist=array();
	system("md \"".$subfolder."\\res\\testdata\"")."\n";
	if($handle=opendir($testdatafolder)){
		while (($file = readdir($handle))!==false) {
			$filename=pathinfo($file);
			if(is_numeric($filename["filename"])){
				$testdatalist[$filename["filename"]][$filename["extension"]]=true;
			}
		}
		closedir($handle);
	}else {
		fwrite(STDOUT, "Error: opendir\n");
	}
	foreach ($testdatalist as $key => $value) {
		if($value["in"]&&$value["out"]){
			system("copy \"".$testdatafolder."\\".$key.".in\" \"".$subfolder."\\res\\testdata\\".$key.".in\"");
			system("copy \"".$testdatafolder."\\".$key.".out\" \"".$subfolder."\\res\\testdata\\".$key.".out\"");
		}else if($value["in"]){
			echo $key." no out\n";
		}else if($value["out"]){
			echo $key." no in\n";
		}
	}
	$conf=new stdClass;
	$conf->timelimit=$timelimit;
	$conf->memlimit=$memlimit;
	$conf->compile="g++";
	$conf->score="rate";
	$conf->check="diff";
	$conf->test=array();
	while(count($testdatalist)!=0){
		$input=0;
		$templist=array();
		while($input!=-1){
			echo "input testdata index (end with -1): ";
			$index=getstdinline();
			if($index==-1)break;
			else if(preg_match("/(\d+)-(\d+)/",$index,$match)){
				for($i=$match[1];$i<=$match[2];$i++){
					$templist[]=(int)$i;
				}
			}else {
				$templist[]=(int)$index;
			}
		}
		echo "input testdata ".implode(",",$templist)." score (end with -1): ";
		$score=getstdinline();
		if($score==-1)break;
		$conf->test[]=array("data"=>$templist,"weight"=>(int)$score);
	}
	file_put_contents($subfolder."\\conf.json", json_encode($conf, JSON_PRETTY_PRINT));
}
?>
