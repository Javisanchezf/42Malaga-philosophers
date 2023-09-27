<div id="header" align="center">
  <img src="https://github.com/Javisanchezf/media/blob/main/pc-gif.webp" width="200"/>
</div>

<h1 align="center">42 Málaga Philosophers</h1>

> School 42 Málaga project.

This repository contains all the files for the Philosophers project in the School 42 Málaga curriculum.

<h2 align="center">
	<a href="#about">About</a>
	<span> · </span>
	<a href="#requirements">Requirements</a>
	<span> · </span>
	<a href="#instructions">Instructions</a>
	<span> · </span>
	<a href="#testing">Testing</a>
	<span> · </span>
	<a href="#tips">Tips</a>
	<span> · </span>
	<a href="#license">License</a>
</h2>

## About

The Philosophers project is designed to test your knowledge of multithreading and synchronization in C. In this project, you will implement the dining philosophers problem, where a group of philosophers must compete for access to a limited number of resources (forks) to eat. You will need to ensure that the philosophers can eat without deadlocks or conflicts.
[You can find more information in the project subject](https://github.com/Javisanchezf/42Malaga-pdfs/blob/main/philosophers_subject.pdf).

The code in this repository follows [the rules of the Norminette](https://github.com/Javisanchezf/42Malaga-pdfs/blob/master/norme.pdf).

## Requirements

The project is written in __C language__ and requires the following:

- Compiler `gcc`.
- Standard libraries:
  - `<stdlib.h>`
  - `<unistd.h>`
  - `<pthread.h>`

## Instructions

### 1. Download the repository

To download the repository, open a terminal and run:

```
git clone --recursive https://github.com/Javisanchezf/42Malaga-philosophers.git
cd 42Malaga-philosophers
```

### 2. Compiling the library

To compile the library, go to its path and run:

```
cd philo
make
```

Or you can compile the bonus part with:
```
cd philo_bonus
make
```

### 3. Cleaning all binary (.o) executable files (.a) and the program

To delete all files generated with make, go to the path and run:
```
make fclean
```

### 4. Using it


To run the program, use the following command:


```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_to_eat]
```
Replace the placeholders with the desired values for the simulation. For example:

```
./philo 5 800 200 200 7
```
## Tips

- Use the sanitaze flag when compiling (cc *.c -fsanitize=thread -g -o philo_sanitize) or [valgrind](https://valgrind.org/docs/manual/quick-start.html) to see the datarace.
- Be careful with variables you access from different threads. Create a mutex for each variable that you can access if necessary.
- Be careful that they cannot speak at the same time, put a mutex protecting your printf.
- Be especially careful when it is 0 or 1 philosopher.
- Make the philosophers left/right handed so there are no conflicts when picking up the forks 😎 .
- Create your own sleep function so that the times are more exact according to the current time.
- __CHALLENGE__: Imagine that philosophers are sleepwalkers and the sleeping time is 0. Make sure your program doesn't hang.

## Testing
To test the program, you can try different combinations of parameters and observe how the philosophers behave. Pay attention to how they compete for forks and whether they are able to eat without conflicts.

- IMPORTANT: For these tests compile the code only with the flags -Wall -Werror -Wextra -pthread. Since if you add Sanitize or Valgrind it will slow down the times and will not give exact results.

<h3 align="center">BASIC LEVEL TEST </h3>
SURVIVE:

```
./philo 4 410 200 200 10 | grep "is eating" | wc -l
```
At least 40 must be obtained.
```
cc *.c -fsanitize=thread -g -o philo_sanitize
./philo_sanitize 4 410 100 100 8
```
No Datarace notices should appear.

DEAD:

```
./philo 0 410 200 200 1
```
```
./philo 1 410 200 200 1
```
```
./philo 5 410 200 200 10
```
<h3 align="center">HARDCORE LEVEL TEST </h3>

SURVIVE:

```
./philo 2 100 50 50 10
```
```
./philo 2 100 50 0 10
```
```
./philo 2 1 0 0 100
```
```
./philo 1 1 0 0 0
```
```
./philo 100 50 1000 1000 0
```
DEAD:

```
./philo 2 100 51 0 10
```
```
./philo 2 100 50 51 10
```
```
./philo 4 400 201 0 10
```
```
./philo 2 2 3 0 1
```

## License
This work is licensed under a [Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-nc-sa/4.0/).

You are free to:
* Share: copy and redistribute the material in any medium or format.
* Adapt: remix, transform, and build upon the material.

Under the following terms:
* Attribution: You must give appropriate credit, provide a link to the license, and indicate if changes were made. You may do so in any reasonable manner, but not in any way that suggests the licensor endorses you or your use.
* NonCommercial: You may not use the material for commercial purposes.
* ShareAlike: If you remix, transform, or build upon the material, you must distribute your contributions under the same license as the original.

<h3 align = right>Share the content!</h3>

[<img src="https://github.com/Javisanchezf/media/blob/main/whatsapp-icon.png" width="50" height="50" align = right></img>](https://api.whatsapp.com/send?text=Hey!%20Check%20out%20this%20cool%20repository%20I%20found%20on%20Github.%20%0ahttps://github.com/Javisanchezf/42Malaga-philosophers)
[<img src="https://github.com/Javisanchezf/media/blob/main/telegram-icon.webp" width="50" height="50" align = right></img>](https://t.me/share/url?url=https://github.com/javisanchezf/42Malaga-philosophers&text=Hey!%20Check%20out%20this%20cool%20repository%20I%20found%20on%20Github.)
[<img src="https://github.com/Javisanchezf/media/blob/main/twitter-icon.png" width="50" height="50" align = right></img>](https://twitter.com/intent/tweet?url=https://github.com/Javisanchezf/42Malaga-philosophers&text=Hey!%20Check%20out%20this%20cool%20repository%20I%20found%20on%20Github)
[<img src="https://github.com/Javisanchezf/media/blob/main/linkedin-icon.png" width="50" height="50" align = right></img>](https://www.linkedin.com/sharing/share-offsite/?url=https://github.com/javisanchezf/42Malaga-philosophers)
