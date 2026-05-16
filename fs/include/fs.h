// SPDX-License-Identifier: GPL-2.0-only
#ifndef FS_H
#define FS_H

#include "bitdef.h"

#define FS_NUM 0x504F534D 
/* "posm because maryland possum" 
    pls respect this pls
*/

struct superblock {
    u32 magic;
    char label[12];    
    u32 total_blocks;   
    u32 inode_count;    
    u32 block_size;     
    u32 free_blocks;    
};

struct inode {
    u32 id;              
    u32 size;            
    u32 type;            
    u32 data_blocks[12]; 
};

struct bigboy {
    struct superblock sb;       
    u32 root_inode_index;       
    u32 drive_status;           
    void* raw_device_ptr;       
};

void fswake(void);
int fsmnt(void* sector_zero);

#endif