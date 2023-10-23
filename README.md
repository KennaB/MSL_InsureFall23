# C++ Profiling with gperftools
This project showcases the profiling capabilities of `gperftools` using a deliberately inefficient Fibonacci calculator and a Mandelbrot set generator.

## Flow
- **Initialization**: With the Docker image built and the container initiated, our environment is set up with the necessary dependencies and our C++ program is ready to run.
    
- **Execution & Profiling**: When the container is started, the `run.sh` script runs the main C++ application. The program computes the Fibonacci sequence in a deliberately inefficient manner multiple times and then generates an image of the Mandelbrot set. These computations are profiled using `gperftools`.
    
- **Visualization**: The profiling data is then converted into a flamegraph format, providing a visual representation of where the CPU time is being spent during the execution of our program. Flamegraphs make it easy to pinpoint which functions or operations are consuming the most resources, enabling developers to optimize their code more effectively.
    
- **Serving the Flamegraph**: An HTTP server is started, serving on port 8080 of the container, allowing users to access and view the flamegraph (`out.svg`) via a web browser. This means that anyone with access to the container's IP and port can view this visualization without needing any additional tools or setups on their end.
    
- **Cleanup**: Thanks to the Docker command used, once the container process completes or is stopped, the container instance will be cleaned up automatically, ensuring there's no residual clutter on the host system.

## Before we begin

Ensure you have the following installed:

- [Docker](https://www.docker.com/products/docker-desktop)

## Project Structure

- **Dockerfile**: Contains the build instructions for the Docker image. This sets up an environment with all necessary dependencies and builds the C++ program.
- **main.cpp**: Contains the primary C++ code that demonstrates the Fibonacci calculation and Mandelbrot set generation.
- **run.sh**: A shell script that runs the C++ program with profiling enabled, converts the profiling data into a flamegraph format, and starts an HTTP server to serve the generated flame graph.

## Building the Docker Image

First things first, make sure you're in the right directory where these files are. In your terminal, navigate to the project's folder using the cd command.

Once you're there, type the below command:

`docker build -t cpp_gperftools .`

This will create a Docker image named `cpp_gperftools`.

This command is used to build a Docker image from the provided Dockerfile.

- `docker build`: This is the primary Docker command used to build images from a Dockerfile.
    
- `-t cpp_gperftools`: The `-t` flag is used to specify a name (and optionally a tag, in the format `name:tag`) for the image. In this case, the image will be named `cpp_gperftools`. If no tag is provided, Docker will use the `latest` tag by default.
    
- `.`: This refers to the current directory's context. Docker will look for a file named `Dockerfile` in this directory and use it as the instructions for building the image. Any files or directories in this context can be used in the Dockerfile with commands like `COPY` or `ADD`.
## Running the Application

Once the image has been built, run the application using the following command:

`docker run -p 8080:8080 --rm cpp_gperftools`

This command is used to create and start a container instance from a given image.

- `docker run`: This is the primary Docker command used to run a container from an image.
    
- `-p 8080:8080`: The `-p` flag is used to publish a container's port(s) to the host. In this case, it's mapping port 8080 on the host to port 8080 on the container. The format is `host_port:container_port`. This means that if the container has a service running on port 8080, it can be accessed from the host machine at `http://localhost:8080`.
    
- `--rm`: This flag automatically removes the container when it exits. This is useful for keeping the host system clean, as it ensures that temporary containers used for short tasks won't clutter the system. Without this flag, you'd have to manually remove the container using `docker rm`.
    
- `cpp_gperftools`: This specifies the name of the Docker image from which the container will be created. If the image has multiple tags, Docker will use the `latest` tag by default, unless another tag is specified (e.g., `cpp_gperftools:1.0`).

After the program has executed, you can view the flame graph of the profiling data by navigating to `http://localhost:8080` in your web browser and opening the `out.svg` file.

## Understanding the Code

- **Fibonacci**: The Fibonacci sequence is calculated using a deliberately inefficient recursive method to simulate CPU-intensive computation.
    
- **Mandelbrot Set**: The Mandelbrot set generator creates a visual representation of the Mandelbrot set and saves it as both a PGM and PNG image file.
    
### Adjusting Fibonacci Computations

To change the value of `n` for which the Fibonacci sequence is computed:

1. Open `main.cpp` in your favorite text editor.
2. Locate the line `int n = 70;`.
3. Modify the value `70` to your desired integer for which you'd like to compute the Fibonacci sequence.
4. Save the changes and rebuild the Docker image to see the effects.
Both computations are profiled using `gperftools`, and the result is visualized using a flame graph.
### Modifying Mandelbrot Dimensions

To adjust the width and height of the generated Mandelbrot image:

1. Open `main.cpp`.
2. Locate the lines with the constants `WIDTH` and `HEIGHT`:
`const int WIDTH = 800; const int HEIGHT = 800;`
3. Modify the values `800` for both `WIDTH` and `HEIGHT` to your preferred dimensions.
4. Save the changes and rebuild the Docker image.

## Additional Notes

- **Rebuilding the Image**: Anytime you make a change in the code, remember to rebuild the Docker image using the command `docker build -t cpp_gperftools .` so that the changes are reflected in the next container run.
- **High Memory or CPU Usage**:
	- **Problem**: The program or Docker container is consuming a lot of memory or CPU.
	- **Solution**: This might be expected, especially when computing larger Fibonacci numbers or generating high-resolution Mandelbrot images. Consider reducing the Fibonacci `n` value or the Mandelbrot dimensions if resource usage is a concern.
- **Accessing the HTTP Server**:
	- **Problem**: Unable to access the flamegraph via a web browser.
	- **Solution**: Ensure the Python HTTP server started correctly. Also, check your firewall or network settings if you're unable to access port 8080 from your host machine.

## Tools & Libraries

- **Docker**: A platform for developing, shipping, and running applications in containers.
  - [Docker Official Website](https://www.docker.com/)
  - [Docker Documentation](https://docs.docker.com/)

- **Ubuntu**: A popular Linux distribution.
  - [Ubuntu Official Website](https://ubuntu.com/)
  - [Ubuntu Docker Images on Docker Hub](https://hub.docker.com/_/ubuntu)

- **gperftools**: Google Performance Tools, a collection of performance analysis tools.
  - [gperftools GitHub Repository](https://github.com/gperftools/gperftools)
  - [gperftools Documentation](https://gperftools.github.io/gperftools/)

- **FlameGraph**: A visualization tool to create interactive flame graph visualizations from profiled code.
  - [FlameGraph GitHub Repository](https://github.com/brendangregg/FlameGraph)
  - [FlameGraph Introduction by Brendan Gregg](http://www.brendangregg.com/flamegraphs.html)

- **libpng**: The official PNG reference library for reading and writing PNG files.
  - [libpng Official Website](http://www.libpng.org/pub/png/libpng.html)
  - [libpng Documentation](http://www.libpng.org/pub/png/libpng-manual.txt)

- **Python**: A popular high-level programming language.
  - [Python Official Website](https://www.python.org/)
  - [Python Documentation](https://docs.python.org/3/)
