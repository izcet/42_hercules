## 42_hercules
The weekly challenges for the *Hercules* project series.
Modeled after the trials of the Greek Demigod Hercules in flavor, each challenge is unique and focuses on a different aspect of programming and development.

TODO:
  - Add links to all the subject pages.
  - Provide links to more detailed resources for each project.

### Nemean Lion
> This week's project was a very basic introduction to `ssh` and ports.
> The requirement was a script that would change the default `sshd` port on a machine to a new port and restart the service.

### Lernaean Hydra
The objective was to create a server that would listen for a connection, accept, and respond to the string `"ping"` with two `"pong"`s.
I went above and beyond and implemented `fork()` to handle multiple client connections, and also signal handling to exit cleanly.

### Ceryneian Hind
~~This week's project was an introduction to web requests and APIs.~~
I forgot to register for this week and was unable to participate.

### Erymanthian Boar
This project was an introduction to timed linux commands, using `at` rather than `cron` for a single event.
The script I provided to be executed `at [time]` was `bomb.sh`, a self-destructive script riddled with escape codes for humorous text.

### Augean Stables
This project was supposed to be a challenge in memory managment, but due to time mismanagement of the staff an incomplete problem set was pushed.
The solution was to match up some `free()` commands to stop the excessive `malloc()` memory leaks.

### Stymphalian Birds
A project aimed at reducing the amount of time and overhead taken up by starting a new code project.
My script sets up the initial git repository, lays out the structure and initial `Makefile` and `inc/[header].h` files.
Then I include other code libraries as needed and prompt the user for the remotes that this project will be pushed to.
My work is focused primarily on C project initialization.

### Cretan Bull
An introduction to programming in Assembly, this project uses the School's custom COREWAR engine.
The task is to create a Hero (written in our custom RedCode) that can survive and kill off other Heroes in the Corewar Arena.

### Mares of Diomedes
An introduction to Fork Bombs.
This two-part project required us to come up with a script that could disarm a `fork()` bomb executable.
We then had to write our own fork bomb to be just as devastating if not more.
I opted not to write out the spam of text files created by the original, instead my variant ignores the various `SIGNALS` sent to it to be harder to kill.
