/* This has not been compiled or tested on an IDE. Some assumptions have been made, such as the file 
 * needs to be closed before it is reopened.
 * /
struct file_essentials
{
  uint32 ex_val;
  uint32 remaining_bits;
};

#define NBITSPERBYTE 8
struct file_essentials read_op, write_op;

int bfread (uint32 *rval, int reqbits, BFILE* bfp)
{
  // Number of bytes requested to be read
  int nbytestoread = ceil ((reqbits - read_op.remaining_bits) / NBITSPERBYTE);
  
  
   if ((reqbits <= 0) || (reqbits > 32))
     return -1;
  if (bfp == NULL)
    return -1;
  
  uint32_t retval;
  int rc;
  // if number of bytes is more than 0
  if (nbytestoread > 0)
  {
    
    uint32_t frval;
    // Read Nbytes using fread API
     rc = fread(&frval, 1, (nbytestoread), bfp);
    // pack the return value with buffered bits and newly read bits
    retval = (ex_val << (reqbits - read_op.remaining_bits)) | (frval >> nbytestoread * NBITSPERBYTE - reqbits);
    // Update the number of bits available in buffer for the consecutive reads
    read_op.remaining_bits = (nbytestoread * NBITSPERBYTE) - reqbits + read_op.remaining_bits;
    // override the buffer with remaining bits
    ex_val = frval & (~(1 << read_op.remaining_bits));
  }
  else 
  {
    // if we already have enough bits in the buffer.
    retval = ex_read_val << reqbits;
    read_op.remaining_bits = read_op.remaining_bits - reqbits;
  }
  *rval = retval;
  if (rc < 0)
    return -2;
}


int bfwrite(uint32 wvalue, int wbits, BFILE* bfp)
{
   int nbytestowrite = floor((wbits + write_op.remaining_bits) / NBITSPERBYTE);
   uint32 retval;
   int rc;
  
   if ((wbits <= 0) || (wbits > 32))
     return -1;
  if (bfp == NULL)
    return -1;
  
  
  if (nbytestowrite > 0)
  {
    
    retval =  (write_op.ex_val << (nbytestowrite * NBITSPERBYTE -   write_op.remaining_bits)) | (wvalue >> (wbits + write_op.remaining_bits - (nbytestowrite * NBITSPERBYTE)));
    write_op.remaining_bits = wbits - (nbytestowrite * NBITSPERBYTE) + write_op.remaining_bits;
    write_op.ex_val = wvalue & (~(1 << write_op.remaining_bits));
     rc = fwrite(retval, nbytestowrite, bfp);
  }
  else
  {
    write_op.ex_val = (write_op.ex_val << wbits) | (wvalue);
    write_op.remaining_bits += wbits;
  }
  
  if ( rc < 0)
  return -2;
}
    
BFILE* bfopen(char *fname, int mode)
{
  fopen(fname, mode);
  write_op.ex_val = 0
  write_op.remaining_bits = 0;
  read_op.ex_val = 0;
  write_op.remaining_bits = 0
}

BFILE* bfclose(char *fname)
{
  fclose(fname);
}
