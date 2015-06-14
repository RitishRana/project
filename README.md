Steps to use the project:
1)install Redis
	http://redis.io/download

2)we also need hiredis: Has been included in the hiredis/include (No need to do anything)

3)Download curl library c/c++ : sudo apt-get install libcurl4-gnutls-dev

4)Now do the make and we'll get main.exe .

5) for feeding and getting from redis cache server we can do:  ./main.exe pune mumbai 14-06-2015.
	date:DD-MM-YYYY

6) For the second part: webpage: Download codeigniter from http://www.codeigniter.com/download and place it in the apache server director.

7) Rename the folder as ci and place hiredis folder downloaded inside ci folder.

8) Place the Redis.php to the path: codeigniter_folder_apache_server(ci)/application/controllers.

9) Finally paste routofy.php to the folder just outside codeigniter_folder_apache_server(ci).

10) Last open the browser: localhost/routofy.php or localhost/path_to_routofy.php
