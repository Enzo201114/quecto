ENTRY(_start)

SECTIONS
{

    . = 0x08048000 + SIZEOF_HEADERS;

    .text : {
        *(.text)
        *(.text.*)
        
        *(.rodata)
        *(.rodata.*)
        
        *(.data)
        *(.data.*)
        
        *(.bss)
        *(.bss.*)
    } :text 

    /DISCARD/ : {
        *(.note*)
        *(.comment*)
        
        *(.eh_frame*)
        *(.eh_frame_hdr)
        
        *(.debug*)
        *(.stab*)
        
        *(.gnu.version*)
        *(.dyn*)
        *(.interp)
        
        *(.got*)
        *(.plt*)
        *(.iplt*)
        *(.igot*)
        
        *(.rel.*)
        *(.rela.*)
        
        *(.ctors)
        *(.dtors)
        *(.jcr)
    }
}

PHDRS
{
    text PT_LOAD FLAGS(7); 
}