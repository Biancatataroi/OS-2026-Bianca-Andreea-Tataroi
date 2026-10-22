# Operating Systems — Laboratory 6
## Inside the xv6 File System

### Part 1 — File System Exploration

1. File types:
   - Type 1: Directory
   - Type 2: Regular file
   - Type 3: Device

2. The root directory has inode number 1.
   Both . and .. refer to the root directory itself.

3. An empty directory has a size of 32 bytes.
   It contains two directory entries: . and ..
   Each directory entry occupies 16 bytes.

### Part 2 — mystat and Hard Links

1. The mystat program displays the file type,
   inode number, hard-link count, and file size.

   Before creating a hard link:
   README: file, inode 2, links 1, size 2441 bytes

   After creating a hard link:
   README: file, inode 2, links 2, size 2441 bytes
   r2: file, inode 2, links 2, size 2441 bytes

   After removing README, the remaining link
   should have a link count of 1.

   Both filenames refer to the same inode.
   Removing one filename does not immediately
   delete the file data.

2. In kernel/sysfile.c, sys_unlink decreases
   the link count using:

   ip->nlink--;

   Data blocks are freed when the link count
   reaches zero and no active inode references
   remain.

3. The on-disk inode structure contains:
   - type
   - major
   - minor
   - nlink
   - size
   - addrs

### Part 3 — File System Limits

1. The maximum filename length is 14 bytes.

   DIRSIZ = 14

   The directory name averyveryverylongname
   was displayed as averyveryveryl.

2. Maximum file size:

   BSIZE = 1024
   NDIRECT = 12
   NINDIRECT = 256

   Maximum size = (12 + 256) * 1024
                = 274432 bytes
                = 268 KiB

3. Disk layout:

   Total blocks: 2000
   Metadata blocks: 47
   Log blocks: 31
   Inode blocks: 13
   Bitmap blocks: 1
   Data blocks: 1953

### Part 4 — Recursive Find

The find program recursively searches for
files and directories matching a given name.

Command:
find . r2

Output:
./a/b/r2
./a/r2
./r2

Command:
find a b

Output:
a/b

Both tests completed successfully.

### Conclusion

In this laboratory, I explored the internal
structure of the xv6 file system and learned
how directories, inodes, and hard links work.

I implemented the mystat program to examine
file metadata and the find program to search
directories recursively.

I also investigated file system limitations,
including block sizes, filename lengths,
and maximum file sizes.
