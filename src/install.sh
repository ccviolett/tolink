sudo rm /usr/bin/tolink
sudo rm /usr/bin/to
sudo rm -r /usr/share/tolink
sudo cp ./tolink /usr/bin/tolink
sudo cp ./tolink /usr/bin/to
sudo chmod a+x /usr/bin/tolink
sudo chmod a+x /usr/bin/to
sudo mkdir -p /usr/share/tolink/doc
sudo cp ./doc/* /usr/share/tolink/doc
sudo mkdir -p /usr/share/tolink/src
sudo cp ./src/* /usr/share/tolink/src
sudo chmod a+x /usr/share/tolink/src/*

