# license-server

TCP/IP server-client application 


build:
  g++ -o ./pgsqltest ./pgsqltest02.cpp -I /opt/libpqxx/include -L /opt/libpqxx/lib -lpq -lpqxx 
  
run:
  ./pgsqltest
  
  
exeptions:


  Servervice postgresql is down:
  
  
    terminate called after throwing an instance of 'pqxx::broken_connection'
      what():  could not connect to server: Connection refused
            Is the server running on host "127.0.0.1" and accepting
            TCP/IP connections on port 5432?


  
