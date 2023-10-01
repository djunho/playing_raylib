# Playing with RayLib

This repo is to play with the [raylib](https://www.raylib.com/) framework.

Use make to compile it

# Desktop compilation
```
make
# or make src/ball
```

To run, execute the desired executable
```
./src/ball
```

# Web

First, compile the raylib for the web. Check the official [doc](https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)).

```
RAYLIB_PATH=./../raylib make -f Makefile.Web src/ball
```

To open the HTML, run a web server.
```
python -m http.server 8080
```

Then open the link: [http://0.0.0.0:8080/src/ball.html](http://0.0.0.0:8080/src/ball.html)
