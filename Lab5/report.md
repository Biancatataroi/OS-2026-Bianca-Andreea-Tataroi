# Operating Systems - Lab 5
## The File System with Your Own Hands

Student: Tataroi Bianca-Andreea
Group: FAF-242
University: Technical University of Moldova

## Part 1 - The Tree and File Types

1. File types:
   /etc - directory
   /etc/passwd - regular file
   /bin - symbolic link
   /dev/null - character device
   /tmp - directory

2. /bin is a symbolic link pointing to /usr/bin.

3. Device types:
   /dev/null is a character device (c).
   /dev/sda is a block device (b).

4. Directory sizes:
   /var/log = 135 MB
   /usr = 5.0 GB

   The /usr directory is approximately 4.9 GB larger
   than /var/log because it contains installed programs,
   libraries, and other system resources.

## Part 2 - Inodes and Links

1. The inode number of notes.txt was 527788.
   The Links field shows the number of hard links.

2. After deleting notes.txt, hard.txt remained readable
   because both names referred to the same inode.
   The rm command removes a directory entry.

3. soft.txt became a broken symbolic link after hard.txt
   was deleted. Its size was 8 bytes because the target
   path "hard.txt" contains 8 characters.

4. A new directory has 2 links: its name in the parent
   directory and its own "." entry.
   Each new subdirectory adds another link through "..".
   Therefore, creating x and y increased the count to 4.

5. one.txt had a logical size of 2 bytes but occupied
   4.0 KB of disk space due to filesystem block allocation.
   big.img had a logical size of 1 GB but used 0 bytes
   because it was created as a sparse file.

## Part 3 - Permissions

1. Permission examples:
   600 = rw------- (private file)
   644 = rw-r--r-- (regular readable file)
   755 = rwxr-xr-x (executable or directory)
   700 = rwx------ (private directory)

2. chmod 000 removes all permissions.
   Ownership does not automatically grant read access.

3. My umask was 0002.
   new.txt received permissions 664.
   newdir received permissions 775.

4. Directory read permission allows listing filenames.
   Execute permission allows accessing files by name.
   With read-only permission, ls worked but cat failed.
   With execute-only permission, ls failed but cat worked.

5. The s in /usr/bin/passwd indicates setuid.
   It allows the program to execute with root privileges.
   The t in /tmp indicates the sticky bit, which restricts
   deletion or renaming of other users' files.

## Part 4 - Disks and the Kernel

1. Disk structure:
   sda - 25 GB
   sda1 - 1 GB, mounted at /boot/efi
   sda2 - 23.9 GB, mounted at /
   Root filesystem type: ext4

2. Root filesystem usage:
   Total: 24 GB
   Used: 7.7 GB
   Available: 15 GB
   Usage: 35%

3. CPU and RAM:
   Logical processors: 2
   Total RAM: approximately 3.3 GiB

4. /proc/self/status displayed "head".
   This happens because /proc/self refers to the
   process accessing the file.

## Conclusion

In this laboratory, I explored the Linux filesystem
structure, identified file types, and investigated inodes,
hard links, and symbolic links. I also tested file and
directory permissions, including setuid and sticky bits.
Finally, I examined disk partitions, filesystem usage,
CPU information, memory, and process data through /proc.
The experiments helped me understand how Linux manages
files, storage, and access permissions.
