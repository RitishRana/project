<?php
/*
*	Name	    :	Ritish
*	Assignment  :	Controllor Of MVC
*	Date	    :	13-June-2015
*/

defined('BASEPATH') OR exit('No direct script access allowed');

class Redis extends CI_Controller {

	public function index()
	{
		echo "Search for buses using url: localhst/ci/index.php/redis/search/from_city/to_city/date(DD-MM-YYYY)";
	}
	public function search($city1,$city2,$date)
	{
		$str="hiredis/./a.out ".$city1." ".$city2." ".$date;
		$output = shell_exec($str);		//  Calling the C++ program from the script
		$this->load->library('table');		//  add the output of C++ program in the table 
		$string = str_replace(array("\\","\r"),"",$output);
		$phpArray = json_decode($string, true);
		$this->table->set_heading('S.No1', 'Traveller', 'Departure Time','Arival Time','Fare(Rs.)');
		foreach ($phpArray['data']['routes'] as $key=>$value) {
    			foreach ($value as $k=>$v ) {
			if($k=='Fare')
			    $fare=$v;
			if($k=='ArrivalTime')
			    $at=preg_replace('(.*T)', '', $v);
			if($k=='DepartureTime')
			    $dt=preg_replace('(.*T)', '', $v);
			if($k=='CompanyName')
			    $traveller=$v;   
    			}
			$this->table->add_row(intval($key)+1,$traveller ,$dt ,$at,$fare);	//  adding row to table
			
		}

		echo $this->table->generate();
		
	}
	
}
