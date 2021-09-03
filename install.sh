if [ "$TRAVIS_OS_NAME" = "linux" ]; then
  wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip
  wget -O opencv_contrib.zip https://github.com/opencv/opencv_contrib/archive/master.zip
  unzip opencv.zip
  unzip opencv_contrib.zip
  mkdir -p build && cd build
  cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-master/modules ../opencv-master
  cmake --build .
  cd .. && sudo make install
elif [ "$TRAVIS_OS_NAME" = "windows" ]; then
  choco install opencv /InstallationPath:C:/deps /Environment:C:/deps
fi
