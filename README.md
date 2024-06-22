# zoot

A simple C++ visualization of two players with battling pets that move randomly across a board. They battle if they run come within two squares of each other.<br><br> I was playing pokemon and wanted to make a very high level base for it with which I can play around.

### Run Instructions
The following instructions have only been verified on MacOS Sonoma 14.5.

0. install Docker Desktop and make sure it is running<br>

1. run XQuartz<br>
```open -a XQuartz```

2. allow connections from the localhost<br>
```xhost + 127.0.0.1```

3. give execution permission for the run script<br>
```chmod +x run_and_cleanup.sh```

3. run the docker container using the provided script<br>
```./run_and_cleanup.sh```<br>
