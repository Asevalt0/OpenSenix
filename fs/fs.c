// SPDX-License-Identifier: GPL-2.0-only
#include "fs.h"
#include "string.h"

static struct bigboy live_controller;

void fswake(void) {
    live_controller.drive_status = 0; live_controller.root_inode_index = 0;
    live_controller.raw_device_ptr = (void*)0; live_controller.sb.magic = 0;
    live_controller.sb.total_blocks = 0; live_controller.sb.inode_count = 0;
    live_controller.sb.block_size = 0; live_controller.sb.free_blocks = 0;

    for (int i = 0; i < 12; i++) {
        live_controller.sb.label[i] = 0;
    }
}


int fsmnt(void* disk_sector_zero) {
    if (disk_sector_zero == (void*)0) {
        return -1; 
    }

    struct superblock* disk_sb = (struct superblock*)disk_sector_zero;

    
    if (disk_sb->magic != FS_NUM) {
        return -2; 
    }

   
    if (strcmp(disk_sb->label, "cutepossum") != 0) {
        return -3; 
    }

  
    live_controller.raw_device_ptr = disk_sector_zero; live_controller.drive_status   = 1; 
    live_controller.root_inode_index = 2; live_controller.sb.magic                           = disk_sb->magic;
    live_controller.sb.total_blocks = disk_sb->total_blocks; live_controller.sb.inode_count  = disk_sb->inode_count;
    live_controller.sb.block_size   = disk_sb->block_size; live_controller.sb.free_blocks    = disk_sb->free_blocks;

    for (int i = 0; i < 12; i++) {
        live_controller.sb.label[i] = disk_sb->label[i];
    }

    return 0; 
}

