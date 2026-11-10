/* MODIFICATIONS OF CACHE SIZES */
/* All modifiable parametres for each of the three caches
can be found below. */

typedef enum {
    LRU,
    RANDOM,
    TEMP_SPAT
} replace_t;

typedef enum {
    BACK,
    THROUGH
} write_t;

#define BUS_SIZE 32     // Value in bytes, bus size is same for all all caches

/* L1i */
#define L1I_CACHE_SIZE 32       // Value in KB
#define L1I_ASSOCIATIVITY 4     // Value in x way. 
#define L1I_REPLACEMENT LRU     // Value defined by enum replace_t
#define L1I_LINE_SIZE 64        // Value in bytes
#define L1I_WRITE BACK          // Value defined by enum write_t

/* L1d */
#define L1D_CACHE_SIZE 32       // Value in KB
#define L1D_ASSOCIATIVITY 8     // Value in x way. 
#define L1D_REPLACEMENT LRU     // Value defined by enum replace_t
#define L1D_LINE_SIZE 64        // Value in bytes
#define L1D_WRITE BACK          // Value defined by enum write_t

/* L2 */ // Inclusive policy
#define L2_CACHE_SIZE 512       // Value in KB
#define L2_ASSOCIATIVITY 8     // Value in x way. 
#define L2_REPLACEMENT LRU     // Value defined by enum replace_t
#define L2_LINE_SIZE 64        // Value in bytes
#define L2_WRITE BACK          // Value defined by enum write_t