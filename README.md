# license-server

build:
  g++ -o ./pgsqltest ./pgsqltest02.cpp -I /opt/libpqxx/include -L /opt/libpqxx/lib -lpq -lpqxx \n
run:
  ./pgsqltest
