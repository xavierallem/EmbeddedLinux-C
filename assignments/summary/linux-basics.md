# Linux Basics
## Commands 

- ### Directories
    - **pwd** - Display current directory path
    ```bash
    $ pwd
    ```
    - **cd** - Change directory
    ```bash
    $ cd name
    ```
    - **cd..** - Go to parent directory
    ```bash
    $ cd ..
    ```
    - **ls** - List the contents of directory
    ```bash
    $ ls
    ```
    - **ls -la** - List the contents of directory with hidden contents
    ```bash
    $ ls -la
    ```
     - **mkdir** - Create new directory named "name"
    ```bash
    $ mkdir name
    ```
- ### Files
     - **rm** - Delete file
    ```bash
    $ rm name
    ```
     - **rm -r** - Delete directory
    ```bash
    $ rm -r name
    ```
     - **rm -f** - Force delete file 
    ```bash
    $ rm -f name
    ```
     - **mv** - Rename file from "old" to "new" 
    ```bash
    $ mv old new
    ```
    Move file "f" to directory "dir"
    
    ```bash
    $ mv f dir
    ```
     - **cp** - Copy file "f" to directory "dir"
    ```bash
    $ cp f dir
    ```
     - **cp -r** - Copy and overwrite existing contents with same name
    ```bash
    $ cp -r dir1 dir2
    ```
     - **touch** - Update file access and modification time of file "f"
    ```bash
    $ touch f
    ```
- ### Search
     - **find** - find all files named "f" in directory "dir"
    ```bash
    $ find dir -name f
    ```
     - **grep** - Output all occurrence of text "test" inside file "f"
    ```bash
    $ grep "test" f
    ```
     - **grep -rl** - Search all files containing text "test" inside directory "dir"
    ```bash
    $ grep -rl "test" dir
    ```
- ### Output
     - **cat** - Output contents of file "f"
    ```bash
    $ cat f
    ```
     - **less** - Output contents of file "f" with pagination etc
    ```bash
    $ less f
    ```
    - **head** - Output first 10 line contents of file "f"
    ```bash
    $ head f
    ```
    - **cmd file** - Direct output of cmd into file
    ```bash
    $ <cmd> <file>
    ```
    - **cmd >> file** -Append the output of cmd to file 
    ```bash
    $ <cmd> <file>
    ```
    - **cmd1 | cmd2** - Direct the output of cmd1 to cmd2
    ```bash
    $ <cmd> <file>
    ```
    - **clear** - Clear commad line window
    ```bash
    $ clear
    ```
- ### Permissions
    - **chmod <file> 755** - Change permissions of file to 755
    ```bash
    $ chmod file 755
    ```
    - **chmod -R 600 <dir>** - Change permissons of all contents in directory "dir" to 600
    ```bash
    $ chmod -R 600 dir 
    ```
    - **chown <user>:<group> <file>** - Change ownership of file to user and group
    ```bash
    $ chown user:group file
    ```
- ### Networking
    - **ping** - Ping "host" and display status
    ```bash
    $ ping host
    ```
    - **whois <domain>** - Output whois information for "domain"
    ```bash
    $ whois domain
    ```
    - **curl** - Download file from url
    ```bash
    $ curl -O <url/to/file>
    ```
    - **ssh** - Connect to "host" with use "username"
    ```bash
    $ ssh username@host
    ```
    - **scp** - copy file "f" to remote host "host" with user "username"
    ```bash
    $ scp f username@host:/remote/path
    ```
- ### Processess
    - **ps ax** - Output currently running processes
    ```bash
    $ ps ax
    ```
    - **top** - Display live info of currently running processes
    ```bash
    $ top
    ```
    - **kill** - Kill process with process Id  "ID"
    ```bash
    $ kill ID
    ```
    
    
    