/***************************************************************************
 *  God Wars Mud improvements copyright (C) 1994, 1995, 1996 by Richard    *
 *  Woolcock.  This mud is NOT to be copied in whole or in part, or to be  *
 *  run without the permission of Richard Woolcock.  Nobody else has       *
 *  permission to authorise the use of this code.                          *
 ***************************************************************************/

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merc.h"

struct flag_stat_type
{
    const struct flag_type *structure;
    bool stat;
};

/*****************************************************************************
 Name:          flag_stat_table
 Purpose:       This table catagorizes the tables following the lookup
                functions below into stats and flags.  Flags can be 
toggled
                but stats can only be assigned.  Update this table when a
                new set of flags is installed.
 
****************************************************************************/
const struct flag_stat_type flag_stat_table[] =
{
/*  {   structure               stat    }, */
    {   area_flags,             FALSE   },
    {   sex_flags,              TRUE    },
    {   exit_flags,             FALSE   },
    {   door_resets,            TRUE    },
    {   room_flags,             FALSE   },
    {   sector_flags,           TRUE    },
    {   type_flags,             TRUE    },
    {   extra_flags,            FALSE   },
    {   wear_flags,             FALSE   },
    {   act_flags,              FALSE   },
    {   affect_flags,           FALSE   },
    {   apply_flags,            TRUE    },
    {   wear_loc_flags,         TRUE    },
    {   wear_loc_strings,       TRUE    },
    {   weapon_flags,           TRUE    },
    {   container_flags,        FALSE   },
    {   liquid_flags,           TRUE    },
               /* END */
    {   0,                      0       }
};

/*****************************************************************************
 Name:          is_stat( table )
 Purpose:       Returns TRUE if the table is a stat table and FALSE if flag.
 Called by:     flag_value and flag_string.
 Note:          This function is local and used only in bit.c.
 ****************************************************************************/
bool is_stat( const struct flag_type *flag_table )
{
    int flag;

    for (flag = 0; flag_stat_table[flag].structure; flag++)
    {
        if ( flag_stat_table[flag].structure == flag_table
          && flag_stat_table[flag].stat )
            return TRUE;
    }
    return FALSE;
}

/*****************************************************************************
 Name:          flag_string( table, flags/stat )
 Purpose:       Returns string with name(s) of the flags or stat entered.
 Called by:     act_olc.c, olc.c, and olc_save.c.
 ****************************************************************************/
char *flag_string( const struct flag_type *flag_table, int bits )
{
    static char buf[512];
    int  flag;

    buf[0] = '\0';

    for (flag = 0; *flag_table[flag].name; flag++)      /* OLC 1.1b */
    {
        if ( !is_stat( flag_table ) && IS_SET(bits, flag_table[flag].bit) )
        {
            strcat( buf, " " );
            strcat( buf, flag_table[flag].name );
        }
        else
        if ( flag_table[flag].bit == bits )
        {
            strcat( buf, " " );
            strcat( buf, flag_table[flag].name );
            break;
        }
    }
    return (buf[0] != '\0') ? buf+1 : "none";
}

const struct flag_type area_flags[] =
{
    {   "none",                 AREA_NONE,              FALSE   },
    {   "changed",              AREA_CHANGED,           FALSE   },
    {   "added",                AREA_ADDED,             FALSE   },
    {   "loading",              AREA_LOADING,           FALSE   },
    {   "",                     0,                      0       }
};

const struct flag_type sex_flags[] =
{
    {   "male",                 SEX_MALE,               TRUE    },
    {   "female",               SEX_FEMALE,             TRUE    },
    {   "neutral",              SEX_NEUTRAL,            TRUE    },
    {   "",                     0,                      0       }
};

const struct flag_type container_flags[] =
{
    {   "closeable",            1,              TRUE    },
    {   "pickproof",            2,              TRUE    },
    {   "closed",               4,              TRUE    },
    {   "locked",               8,              TRUE    },
    {   "",                     0,              0       }
};

const struct flag_type liquid_flags[] =
{
    {   "water",                0,      TRUE    },
    {   "beer",                 1,      TRUE    },
    {   "wine",                 2,      TRUE    },
    {   "ale",                  3,      TRUE    },
    {   "dark-ale",             4,      TRUE    },
    {   "whisky",               5,      TRUE    },
    {   "lemonade",             6,      TRUE    },
    {   "firebreather",         7,      TRUE    },
    {   "local-specialty",      8,      TRUE    },
    {   "slime-mold-juice",     9,      TRUE    },
    {   "milk",                 10,     TRUE    },
    {   "tea",                  11,     TRUE    },
    {   "coffee",               12,     TRUE    },
    {   "blood",                13,     TRUE    },
    {   "salt-water",           14,     TRUE    },
    {   "cola",                 15,     TRUE    },
    {   "cum",                  16,     TRUE    },
    {   "cunt-juice",           17,     TRUE    },
    {   "urine",                18,     TRUE    },
    {   "",                     0,      0       }
};

const struct flag_type weapon_flags[] =
{
    {   "hit",          0,      TRUE    },
    {   "slice",        1,      TRUE    },
    {   "stab",         2,      TRUE    },
    {   "slash",        3,      TRUE    },
    {   "whip",         4,      TRUE    },
    {   "claw",         5,      TRUE    },
    {   "blast",        6,      TRUE    },
    {   "pound",        7,      TRUE    },
    {   "crush",        8,      TRUE    },
    {   "grep",         9,      TRUE    },
    {   "bite",         10,     TRUE    },
    {   "pierce",       11,     TRUE    },
    {   "suck",         12,     TRUE    },
    {   "",             0,      0       }
};

/*
 * What is typed.
 * Neck2 should not be settable for loaded mobiles.
 */
const struct flag_type wear_loc_flags[] =
{
    {   "none",         WEAR_NONE,      TRUE    },
    {   "light",        WEAR_LIGHT,     TRUE    },
    {   "lfinger",      WEAR_FINGER_L,  TRUE    },
    {   "rfinger",      WEAR_FINGER_R,  TRUE    },
    {   "neck",         WEAR_NECK_1,    TRUE    },
    {   "body",         WEAR_BODY,      TRUE    },
    {   "head",         WEAR_HEAD,      TRUE    },
    {   "legs",         WEAR_LEGS,      TRUE    },
    {   "feet",         WEAR_FEET,      TRUE    },
    {   "hands",        WEAR_HANDS,     TRUE    },
    {   "arms",         WEAR_ARMS,      TRUE    },
    {   "shield",       WEAR_SHIELD,    TRUE    },
    {   "about",        WEAR_ABOUT,     TRUE    },
    {   "waist",        WEAR_WAIST,     TRUE    },
    {   "lwrist",       WEAR_WRIST_L,   TRUE    },
    {   "rwrist",       WEAR_WRIST_R,   TRUE    },
    {   "wielded",      WEAR_WIELD,     TRUE    },
    {   "hold",         WEAR_HOLD,      TRUE    },
    {   "face",         WEAR_FACE,      TRUE    },
    {   "",             0,              0       }
};

/*
 * What is seen.
 */
const struct flag_type wear_loc_strings[] =
{
    {   "in the inventory",     WEAR_NONE,      TRUE    },
    {   "as a light",           WEAR_LIGHT,     TRUE    },
    {   "on the left finger",   WEAR_FINGER_L,  TRUE    },
    {   "on the right finger",  WEAR_FINGER_R,  TRUE    },
    {   "around the neck (1)",  WEAR_NECK_1,    TRUE    },
    {   "around the neck (2)",  WEAR_NECK_2,    TRUE    },
    {   "on the body",          WEAR_BODY,      TRUE    },
    {   "over the head",        WEAR_HEAD,      TRUE    },
    {   "on the legs",          WEAR_LEGS,      TRUE    },
    {   "on the feet",          WEAR_FEET,      TRUE    },
    {   "on the hands",         WEAR_HANDS,     TRUE    },
    {   "on the arms",          WEAR_ARMS,      TRUE    },
    {   "about the body",       WEAR_ABOUT,     TRUE    },
    {   "around the waist",     WEAR_WAIST,     TRUE    },
    {   "on the left wrist",    WEAR_WRIST_L,   TRUE    },
    {   "on the right wrist",   WEAR_WRIST_R,   TRUE    },
    {   "on the face",          WEAR_FACE,      TRUE    },
    {   "as a shield",          WEAR_SHIELD,    TRUE    },
    {   "first hand",           WEAR_WIELD,     TRUE    },
    {   "second hand",          WEAR_HOLD,      TRUE    },
    {   "left scabbard",        WEAR_SCABBARD_L,TRUE    },
    {   "right scabbard",       WEAR_SCABBARD_R,TRUE    },
    {   "",                     0                       }
};

const struct flag_type apply_flags[] =
{
    {   "none",                 APPLY_NONE,             TRUE    },
    {   "strength",             APPLY_STR,              TRUE    },
    {   "dexterity",            APPLY_DEX,              TRUE    },
    {   "intelligence",         APPLY_INT,              TRUE    },
    {   "wisdom",               APPLY_WIS,              TRUE    },
    {   "constitution",         APPLY_CON,              TRUE    },
    {   "sex",                  APPLY_SEX,              TRUE    },
    {   "class",                APPLY_CLASS,            TRUE    },
    {   "level",                APPLY_LEVEL,            TRUE    },
    {   "age",                  APPLY_AGE,              TRUE    },
    {   "height",               APPLY_HEIGHT,           TRUE    },
    {   "weight",               APPLY_WEIGHT,           TRUE    },
    {   "mana",                 APPLY_MANA,             TRUE    },
    {   "hp",                   APPLY_HIT,              TRUE    },
    {   "move",                 APPLY_MOVE,             TRUE    },
    {   "gold",                 APPLY_GOLD,             TRUE    },
    {   "experience",           APPLY_EXP,              TRUE    },
    {   "ac",                   APPLY_AC,               TRUE    },
    {   "hitroll",              APPLY_HITROLL,          TRUE    },
    {   "damroll",              APPLY_DAMROLL,          TRUE    },
    {   "saving-para",          APPLY_SAVING_PARA,      TRUE    },
    {   "saving-rod",           APPLY_SAVING_ROD,       TRUE    },
    {   "saving-petri",         APPLY_SAVING_PETRI,     TRUE    },
    {   "saving-breath",        APPLY_SAVING_BREATH,    TRUE    },
    {   "saving-spell",         APPLY_SAVING_SPELL,     TRUE    },
    {   "polymorph",            APPLY_POLY,             TRUE    },
    {   "",                     0,                      0       }
};

const struct flag_type affect_flags[] =
{
    {   "blind",                AFF_BLIND,              TRUE    },
    {   "invisible",            AFF_INVISIBLE,          TRUE    },
    {   "detect-evil",          AFF_DETECT_EVIL,        TRUE    },
    {   "detect-invis",         AFF_DETECT_INVIS,       TRUE    },
    {   "detect-magic",         AFF_DETECT_MAGIC,       TRUE    },
    {   "detect-hidden",        AFF_DETECT_HIDDEN,      TRUE    },
    {   "shadowplane",          AFF_SHADOWPLANE,        TRUE    },
    {   "sanctuary",            AFF_SANCTUARY,          TRUE    },
    {   "faerie-fire",          AFF_FAERIE_FIRE,        TRUE    },
    {   "infrared",             AFF_INFRARED,           TRUE    },
    {   "curse",                AFF_CURSE,              TRUE    },
    {   "flaming",              AFF_FLAMING,            TRUE    },
    {   "poison",               AFF_POISON,             TRUE    },
    {   "protect",              AFF_PROTECT,            TRUE    },
    {   "ethereal",             AFF_ETHEREAL,           TRUE    },
    {   "sneak",                AFF_SNEAK,              TRUE    },
    {   "hide",                 AFF_HIDE,               TRUE    },
    {   "sleep",                AFF_SLEEP,              TRUE    },
    {   "charm",                AFF_CHARM,              TRUE    },
    {   "flying",               AFF_FLYING,             TRUE    },
    {   "pass-door",            AFF_PASS_DOOR,          TRUE    },
    {   "polymorph",            AFF_POLYMORPH,          FALSE   },
    {   "shadowsight",          AFF_SHADOWSIGHT,        TRUE    },
    {   "web",                  AFF_WEBBED,             TRUE    },
    {   "",                     0,                      0       }
};

const struct flag_type act_flags[] =
{
    {   "npc",                  ACT_IS_NPC,             FALSE   },
    {   "sentinel",             ACT_SENTINEL,   TRUE    },
    {   "scavenger",    ACT_SCAVENGER,  TRUE    },
    {   "aggressive",   ACT_AGGRESSIVE, TRUE    },
    {   "stay_area",    ACT_STAY_AREA,  TRUE    },
    {   "wimpy",                ACT_WIMPY,              TRUE    },
    {   "train",                ACT_TRAIN,              TRUE    },
    {   "practice",             ACT_PRACTICE,   TRUE    },
    {   "mount",                ACT_MOUNT,              TRUE    },
    {   "no_parts",             ACT_NOPARTS,    TRUE    },
    {   "no_exp",               ACT_NOEXP,              TRUE    },
    {   "",                     0,                      0       }
};

const struct flag_type wear_flags[] =
{
    {   "take",                 ITEM_TAKE,              TRUE    },
    {   "finger",               ITEM_WEAR_FINGER,       TRUE    },
    {   "neck",                 ITEM_WEAR_NECK,         TRUE    },
    {   "body",                 ITEM_WEAR_BODY,         TRUE    },
    {   "head",                 ITEM_WEAR_HEAD,         TRUE    },
    {   "legs",                 ITEM_WEAR_LEGS,         TRUE    },
    {   "feet",                 ITEM_WEAR_FEET,         TRUE    },
    {   "hands",                ITEM_WEAR_HANDS,        TRUE    },
    {   "arms",                 ITEM_WEAR_ARMS,         TRUE    },
    {   "shield",               ITEM_WEAR_SHIELD,       TRUE    },
    {   "about",                ITEM_WEAR_ABOUT,        TRUE    },
    {   "waist",                ITEM_WEAR_WAIST,        TRUE    },
    {   "wrist",                ITEM_WEAR_WRIST,        TRUE    },
    {   "wield",                ITEM_WIELD,             TRUE    },
    {   "hold",                 ITEM_HOLD,              TRUE    },
    {   "face",                 ITEM_WEAR_FACE,         TRUE    },
    {   "",                     0,                      0       }
};

const struct flag_type type_flags[] =
{
    {   "light",                ITEM_LIGHT,             TRUE    },
    {   "scroll",               ITEM_SCROLL,            TRUE    },
    {   "wand",                 ITEM_WAND,              TRUE    },
    {   "staff",                ITEM_STAFF,             TRUE    },
    {   "weapon",               ITEM_WEAPON,            TRUE    },
    {   "treasure",             ITEM_TREASURE,          TRUE    },
    {   "armor",                ITEM_ARMOR,             TRUE    },
    {   "potion",               ITEM_POTION,            TRUE    },
    {   "furniture",            ITEM_FURNITURE,         TRUE    },
    {   "trash",                ITEM_TRASH,             TRUE    },
    {   "container",            ITEM_CONTAINER,         TRUE    },
    {   "drink-container",      ITEM_DRINK_CON,         TRUE    },
    {   "key",                  ITEM_KEY,               TRUE    },
    {   "food",                 ITEM_FOOD,              TRUE    },
    {   "money",                ITEM_MONEY,             TRUE    },
    {   "boat",                 ITEM_BOAT,              TRUE    },
    {   "npc corpse",           ITEM_CORPSE_NPC,        TRUE    },
    {   "pc corpse",            ITEM_CORPSE_PC,         FALSE   },
    {   "fountain",             ITEM_FOUNTAIN,          TRUE    },
    {   "pill",                 ITEM_PILL,              TRUE    },
    {   "portal",               ITEM_PORTAL,            TRUE    },
    {   "egg",                  ITEM_EGG,               TRUE    },
    {   "voodoo",               ITEM_VOODOO,            TRUE    },
    {   "stake",                ITEM_STAKE,             TRUE    },
    {   "missile",              ITEM_MISSILE,           TRUE    },
    {   "ammo",                 ITEM_AMMO,              TRUE    },
    {   "quest",                ITEM_QUEST,             TRUE    },
    {   "symbol",               ITEM_SYMBOL,            TRUE    },
    {   "book",                 ITEM_BOOK,              TRUE    },
    {   "page",                 ITEM_PAGE,              TRUE    },
    {   "tool",                 ITEM_TOOL,              TRUE    },
    {   "wall",                 ITEM_WALL,              TRUE    },
    {   "",                     0,                      0       }
};

const struct flag_type extra_flags[] =
{
    {   "glow",                 ITEM_GLOW,              TRUE    },
    {   "hum",                  ITEM_HUM,               TRUE    },
    {   "thrown",               ITEM_THROWN,            TRUE    },
    {   "keep",                 ITEM_KEEP,              TRUE    },
    {   "vanish",               ITEM_VANISH,            TRUE    },
    {   "invis",                ITEM_INVIS,             TRUE    },
    {   "magic",                ITEM_MAGIC,             TRUE    },
    {   "nodrop",               ITEM_NODROP,            TRUE    },
    {   "bless",                ITEM_BLESS,             TRUE    },
    {   "anti-good",            ITEM_ANTI_GOOD,         TRUE    },
    {   "anti-evil",            ITEM_ANTI_EVIL,         TRUE    },
    {   "anti-neutral",         ITEM_ANTI_NEUTRAL,      TRUE    },
    {   "noremove",             ITEM_NOREMOVE,          TRUE    },
    {   "inventory",            ITEM_INVENTORY,         TRUE    },
    {   "shadowplane",          ITEM_SHADOWPLANE,       TRUE    },
    {   "loyal",                ITEM_LOYAL,             TRUE    },
    {   "",                     0,                      0       }
};

const struct flag_type door_resets[] =
{
    {   "open and unlocked",    0,              TRUE    },
    {   "closed and unlocked",  1,              TRUE    },
    {   "closed and locked",    2,              TRUE    },
    {   "",                     0,              0       }
};

const struct flag_type exit_flags[] =
{
    {   "door",                 EX_ISDOOR,              TRUE    },
    {   "closed",               EX_CLOSED,              TRUE    },
    {   "locked",               EX_LOCKED,              TRUE    },
    {   "pickproof",            EX_PICKPROOF,           TRUE    },
    {   "",                     0,                      0       }
};

const struct flag_type room_flags[] =
{
    {   "dark",                 ROOM_DARK,              TRUE    },
    {   "no_mob",               ROOM_NO_MOB,            TRUE    },
    {   "indoors",              ROOM_INDOORS,           TRUE    },
    {   "private",              ROOM_PRIVATE,           TRUE    },
    {   "safe",                 ROOM_SAFE,              TRUE    },
    {   "solitary",             ROOM_SOLITARY,          TRUE    },
    {   "no_recall",            ROOM_NO_RECALL,         TRUE    },
    {   "no_teleport",          ROOM_NO_TELEPORT,       TRUE    },
    {   "total_darkness",       ROOM_TOTAL_DARKNESS,    TRUE    },
    /* Leave the bottom part */
    {   "",                     0,                      0       }
};

const struct flag_type sector_flags[] =
{
    {   "inside",       SECT_INSIDE,            TRUE    },
    {   "city",         SECT_CITY,              TRUE    },
    {   "field",        SECT_FIELD,             TRUE    },
    {   "forest",       SECT_FOREST,            TRUE    },
    {   "hills",        SECT_HILLS,             TRUE    },
    {   "mountain",     SECT_MOUNTAIN,          TRUE    },
    {   "swim",         SECT_WATER_SWIM,        TRUE    },
    {   "noswim",       SECT_WATER_NOSWIM,      TRUE    },
    {   "air",          SECT_AIR,               TRUE    },
    {   "desert",       SECT_DESERT,            TRUE    },
    {   "",             0,                      0       }
};

char *room_bit_name( int room_flags )
{
    static char buf[512];

    buf[0] = '\0';
    if ( room_flags & ROOM_DARK         ) strcat( buf, " dark"         );
    if ( room_flags & ROOM_NO_MOB       ) strcat( buf, " no_mobs"      );
    if ( room_flags & ROOM_INDOORS      ) strcat( buf, " indoors"      );
    if ( room_flags & ROOM_PRIVATE      ) strcat( buf, " private"      );
    if ( room_flags & ROOM_SAFE         ) strcat( buf, " safe"         );
    if ( room_flags & ROOM_SOLITARY     ) strcat( buf, " solitary"     );
    if ( room_flags & ROOM_PET_SHOP     ) strcat( buf, " pet_shop"     );
    if ( room_flags & ROOM_NO_RECALL    ) strcat( buf, " no_recall"    );
    if ( room_flags & ROOM_NO_TELEPORT  ) strcat( buf, " no_teleport"  );
    if ( room_flags & ROOM_TOTAL_DARKNESS ) strcat( buf, " total_darkness" );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}



int room_name_bit( char* buf )
{
    if ( !str_cmp( buf, "dark"         ) ) return ROOM_DARK;
    if ( !str_cmp( buf, "no_mobs"      ) ) return ROOM_NO_MOB;
    if ( !str_cmp( buf, "indoors"      ) ) return ROOM_INDOORS;
    if ( !str_cmp( buf, "private"      ) ) return ROOM_PRIVATE;
    if ( !str_cmp( buf, "safe"         ) ) return ROOM_SAFE;
    if ( !str_cmp( buf, "solitary"     ) ) return ROOM_SOLITARY;
    if ( !str_cmp( buf, "pet_shop"     ) ) return ROOM_PET_SHOP;
    if ( !str_cmp( buf, "no_recall"    ) ) return ROOM_NO_RECALL;
    if ( !str_cmp( buf, "no_teleport"  ) ) return ROOM_NO_TELEPORT;
    if ( !str_cmp( buf, "total_darkness" ) ) return ROOM_TOTAL_DARKNESS;
    return 0;
}



int sector_number( char *argument )
{
    if ( !str_cmp( argument, "inside" ) )       return SECT_INSIDE;
    if ( !str_cmp( argument, "city" ) )         return SECT_CITY;
    if ( !str_cmp( argument, "field" ) )        return SECT_FIELD;
    if ( !str_cmp( argument, "forest" ) )       return SECT_FOREST;
    if ( !str_cmp( argument, "hills" ) )        return SECT_HILLS;
    if ( !str_cmp( argument, "mountain" ) )     return SECT_MOUNTAIN;
    if ( !str_cmp( argument, "swim" ) )         return SECT_WATER_SWIM;
    if ( !str_cmp( argument, "noswim" ) )       return SECT_WATER_NOSWIM;
    if ( !str_cmp( argument, "underwater" ) )   return SECT_UNDERWATER;
    if ( !str_cmp( argument, "air" ) )          return SECT_AIR;
    if ( !str_cmp( argument, "desert" ) )       return SECT_DESERT;
    return SECT_MAX;
}



char *sector_name( int sect )
{
    if ( sect == SECT_INSIDE )       return "inside";
    if ( sect == SECT_CITY )         return "city";
    if ( sect == SECT_FIELD )        return "field";
    if ( sect == SECT_FOREST )       return "forest";
    if ( sect == SECT_HILLS )        return "hills";
    if ( sect == SECT_MOUNTAIN )     return "mountain";
    if ( sect == SECT_WATER_SWIM )   return "swim";
    if ( sect == SECT_WATER_NOSWIM ) return "noswim";
    if ( sect == SECT_UNDERWATER )   return "underwater";
    if ( sect == SECT_AIR )          return "air";
    if ( sect == SECT_DESERT )       return "desert";
    return "unknown";
}



/*
 * Return ascii name of an item type.
 */
char *item_type_name( int item_type )
{
    switch ( item_type )
    {
    case ITEM_LIGHT:		return "light";
    case ITEM_SCROLL:		return "scroll";
    case ITEM_WAND:		return "wand";
    case ITEM_STAFF:		return "staff";
    case ITEM_WEAPON:		return "weapon";
    case ITEM_TREASURE:		return "treasure";
    case ITEM_ARMOR:		return "armor";
    case ITEM_POTION:		return "potion";
    case ITEM_FURNITURE:	return "furniture";
    case ITEM_TRASH:		return "trash";
    case ITEM_CONTAINER:	return "container";
    case ITEM_DRINK_CON:	return "drink container";
    case ITEM_KEY:		return "key";
    case ITEM_FOOD:		return "food";
    case ITEM_MONEY:		return "money";
    case ITEM_BOAT:		return "boat";
    case ITEM_CORPSE_NPC:	return "npc corpse";
    case ITEM_CORPSE_PC:	return "pc corpse";
    case ITEM_FOUNTAIN:		return "fountain";
    case ITEM_PILL:		return "pill";
    case ITEM_PORTAL:		return "portal";
    case ITEM_EGG:		return "egg";
    case ITEM_VOODOO:		return "voodoo doll";
    case ITEM_STAKE:		return "stake";
    case ITEM_MISSILE:		return "missile";
    case ITEM_AMMO:		return "ammo";
    case ITEM_QUEST:		return "quest token";
    case ITEM_QUESTCARD:	return "quest card";
    case ITEM_QUESTMACHINE:	return "quest generator";
    case ITEM_SYMBOL:		return "magical symbol";
    case ITEM_BOOK:		return "book";
    case ITEM_PAGE:		return "page";
    case ITEM_TOOL:		return "tool";
    case ITEM_WALL:		return "wall";
    case ITEM_WARD:		return "ward";
    }

    bug( "Item_type_name: unknown type %d.", item_type );
    return "(unknown)";
}

int item_name_type( char *name )
{
    if ( !str_cmp( name, "light"     ) ) return ITEM_LIGHT;
    if ( !str_cmp( name, "scroll"    ) ) return ITEM_SCROLL;
    if ( !str_cmp( name, "wand"      ) ) return ITEM_WAND;
    if ( !str_cmp( name, "staff"     ) ) return ITEM_STAFF;
    if ( !str_cmp( name, "weapon"    ) ) return ITEM_WEAPON;
    if ( !str_cmp( name, "treasure"  ) ) return ITEM_TREASURE;
    if ( !str_cmp( name, "armor"     ) ) return ITEM_ARMOR;
    if ( !str_cmp( name, "potion"    ) ) return ITEM_POTION;
    if ( !str_cmp( name, "furniture" ) ) return ITEM_FURNITURE;
    if ( !str_cmp( name, "trash"     ) ) return ITEM_TRASH;
    if ( !str_cmp( name, "container" ) ) return ITEM_CONTAINER;
    if ( !str_cmp( name, "drink"     ) ) return ITEM_DRINK_CON;
    if ( !str_cmp( name, "key"       ) ) return ITEM_KEY;
    if ( !str_cmp( name, "food"      ) ) return ITEM_FOOD;
    if ( !str_cmp( name, "money"     ) ) return ITEM_MONEY;
    if ( !str_cmp( name, "boat"      ) ) return ITEM_BOAT;
    if ( !str_cmp( name, "corpse"    ) ) return ITEM_CORPSE_NPC;
    if ( !str_cmp( name, "fountain"  ) ) return ITEM_FOUNTAIN;
    if ( !str_cmp( name, "pill"      ) ) return ITEM_PILL;
    if ( !str_cmp( name, "portal"    ) ) return ITEM_PORTAL;
    if ( !str_cmp( name, "egg"       ) ) return ITEM_EGG;
    if ( !str_cmp( name, "stake"     ) ) return ITEM_STAKE;
    if ( !str_cmp( name, "missile"   ) ) return ITEM_MISSILE;
    if ( !str_cmp( name, "ammo"      ) ) return ITEM_AMMO;

    return 0;
}



/*
 * Return ascii name of extra flags vector.
 */
char *extra_bit_name( int extra_flags )
{
    static char buf[512];

    buf[0] = '\0';
    if ( extra_flags & ITEM_GLOW         ) strcat( buf, " glow"         );
    if ( extra_flags & ITEM_HUM          ) strcat( buf, " hum"          );
    if ( extra_flags & ITEM_INVIS        ) strcat( buf, " invis"        );
    if ( extra_flags & ITEM_MAGIC        ) strcat( buf, " magic"        );
    if ( extra_flags & ITEM_NODROP       ) strcat( buf, " nodrop"       );
    if ( extra_flags & ITEM_ANTI_GOOD    ) strcat( buf, " anti-good"    );
    if ( extra_flags & ITEM_ANTI_EVIL    ) strcat( buf, " anti-evil"    );
    if ( extra_flags & ITEM_ANTI_NEUTRAL ) strcat( buf, " anti-neutral" );
    if ( extra_flags & ITEM_BLESS        ) strcat( buf, " bless"        );
    if ( extra_flags & ITEM_NOREMOVE     ) strcat( buf, " noremove"     );
    if ( extra_flags & ITEM_INVENTORY    ) strcat( buf, " inventory"    );
    if ( extra_flags & ITEM_LOYAL        ) strcat( buf, " loyal"        );
    if ( extra_flags & ITEM_SHADOWPLANE  ) strcat( buf, " shadowplane"  );
    if ( extra_flags & ITEM_THROWN       ) strcat( buf, " thrown"       );
    if ( extra_flags & ITEM_KEEP         ) strcat( buf, " keep"         );
    if ( extra_flags & ITEM_VANISH       ) strcat( buf, " illusion"     );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}


int extra_name_bit( char* buf )
{
    if (!str_cmp( buf, "glow"        ) ) return ITEM_GLOW        ;
    if (!str_cmp( buf, "hum"         ) ) return ITEM_HUM         ;
    if (!str_cmp( buf, "thrown"      ) ) return ITEM_THROWN      ;
    if (!str_cmp( buf, "invis"       ) ) return ITEM_INVIS       ;
    if (!str_cmp( buf, "magic"       ) ) return ITEM_MAGIC       ;
    if (!str_cmp( buf, "nodrop"      ) ) return ITEM_NODROP      ;
    if (!str_cmp( buf, "bless"       ) ) return ITEM_BLESS       ;
    if (!str_cmp( buf, "anti-good"   ) ) return ITEM_ANTI_GOOD   ;
    if (!str_cmp( buf, "anti-evil"   ) ) return ITEM_ANTI_EVIL   ;
    if (!str_cmp( buf, "anti-neutral") ) return ITEM_ANTI_NEUTRAL;
    if (!str_cmp( buf, "noremove"    ) ) return ITEM_NOREMOVE    ;
    if (!str_cmp( buf, "inventory"   ) ) return ITEM_INVENTORY   ;
    if (!str_cmp( buf, "loyal"       ) ) return ITEM_LOYAL       ;
    if (!str_cmp( buf, "shadowplane" ) ) return ITEM_SHADOWPLANE ;
    if (!str_cmp( buf, "illusion"    ) ) return ITEM_VANISH      ;
    return 0;
}



/*
 * Returns the name of a wear bit.
 */
char *wear_bit_name( int wear )
{
    static char buf[512];

    buf[0] = '\0';
    if ( wear & ITEM_TAKE        ) strcat( buf, " take"       );
    if ( wear & ITEM_WEAR_FINGER ) strcat( buf, " finger"     );
    if ( wear & ITEM_WEAR_NECK   ) strcat( buf, " neck"       );
    if ( wear & ITEM_WEAR_BODY   ) strcat( buf, " body"       );
    if ( wear & ITEM_WEAR_HEAD   ) strcat( buf, " head"       );
    if ( wear & ITEM_WEAR_LEGS   ) strcat( buf, " legs"       );
    if ( wear & ITEM_WEAR_FEET   ) strcat( buf, " feet"       );
    if ( wear & ITEM_WEAR_HANDS  ) strcat( buf, " hands"      );
    if ( wear & ITEM_WEAR_ARMS   ) strcat( buf, " arms"       );
    if ( wear & ITEM_WEAR_ABOUT  ) strcat( buf, " about"      );
    if ( wear & ITEM_WEAR_WAIST  ) strcat( buf, " waist"      );
    if ( wear & ITEM_WEAR_WRIST  ) strcat( buf, " wrist"      );
    if ( wear & ITEM_WIELD       ) strcat( buf, " hold"       );
    if ( wear & ITEM_WEAR_FACE   ) strcat( buf, " face"       );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}


/*
 * Returns the bit, given a certain name.
 */
int wear_name_bit( char* buf )
{
    if (!str_cmp( buf, "take"       ) ) return ITEM_TAKE;
    if (!str_cmp( buf, "finger"     ) ) return ITEM_WEAR_FINGER;
    if (!str_cmp( buf, "neck"       ) ) return ITEM_WEAR_NECK;
    if (!str_cmp( buf, "body"       ) ) return ITEM_WEAR_BODY;
    if (!str_cmp( buf, "head"       ) ) return ITEM_WEAR_HEAD;
    if (!str_cmp( buf, "legs"       ) ) return ITEM_WEAR_LEGS;
    if (!str_cmp( buf, "feet"       ) ) return ITEM_WEAR_FEET;
    if (!str_cmp( buf, "hands"      ) ) return ITEM_WEAR_HANDS;
    if (!str_cmp( buf, "arms"       ) ) return ITEM_WEAR_ARMS;
    if (!str_cmp( buf, "about"      ) ) return ITEM_WEAR_ABOUT;
    if (!str_cmp( buf, "waist"      ) ) return ITEM_WEAR_WAIST;
    if (!str_cmp( buf, "wrist"      ) ) return ITEM_WEAR_WRIST;
    if (!str_cmp( buf, "hold"       ) ) return ITEM_WIELD;
    if (!str_cmp( buf, "face"       ) ) return ITEM_WEAR_FACE;
    return 0;
}



int act_name_bit( char* buf )
{
    if ( !str_cmp( buf, "sentinel"     ) ) return ACT_SENTINEL;
    if ( !str_cmp( buf, "scavenger"    ) ) return ACT_SCAVENGER;
    if ( !str_cmp( buf, "aggressive"   ) ) return ACT_AGGRESSIVE;
    if ( !str_cmp( buf, "stay_area"    ) ) return ACT_STAY_AREA;
    if ( !str_cmp( buf, "wimpy"        ) ) return ACT_WIMPY;
    if ( !str_cmp( buf, "mount"        ) ) return ACT_MOUNT;
    if ( !str_cmp( buf, "no_parts"     ) ) return ACT_NOPARTS;
    if ( !str_cmp( buf, "no_exp"       ) ) return ACT_NOEXP;
    if ( !str_cmp( buf, "skilled"      ) ) return ACT_SKILLED;
    return 0;
}



/*
 * Return bit vector
 */
int affect_name_bit( char* buf )
{
    if (!str_cmp( buf, "blind"         )) return AFF_BLIND;
    if (!str_cmp( buf, "invisible"     )) return AFF_INVISIBLE;
    if (!str_cmp( buf, "detect-evil"   )) return AFF_DETECT_EVIL;
    if (!str_cmp( buf, "detect-invis"  )) return AFF_DETECT_INVIS;
    if (!str_cmp( buf, "detect-magic"  )) return AFF_DETECT_MAGIC;
    if (!str_cmp( buf, "detect-hidden" )) return AFF_DETECT_HIDDEN;
    if (!str_cmp( buf, "shadowplane"   )) return AFF_SHADOWPLANE;
    if (!str_cmp( buf, "sanctuary"     )) return AFF_SANCTUARY;
    if (!str_cmp( buf, "faerie-fire"   )) return AFF_FAERIE_FIRE;
    if (!str_cmp( buf, "infrared"      )) return AFF_INFRARED;
    if (!str_cmp( buf, "curse"         )) return AFF_CURSE;
    if (!str_cmp( buf, "flaming"       )) return AFF_FLAMING;
    if (!str_cmp( buf, "poison"        )) return AFF_POISON;
    if (!str_cmp( buf, "protect"       )) return AFF_PROTECT;
    if (!str_cmp( buf, "ethereal"      )) return AFF_ETHEREAL;
    if (!str_cmp( buf, "sneak"         )) return AFF_SNEAK;
    if (!str_cmp( buf, "hide"          )) return AFF_HIDE;
    if (!str_cmp( buf, "sleep"         )) return AFF_SLEEP;
    if (!str_cmp( buf, "charm"         )) return AFF_CHARM;
    if (!str_cmp( buf, "flying"        )) return AFF_FLYING;
    if (!str_cmp( buf, "pass-door"     )) return AFF_PASS_DOOR;
    if (!str_cmp( buf, "shadowsight"   )) return AFF_SHADOWSIGHT;
    if (!str_cmp( buf, "rotting"       )) return AFF_ROT;
    if (!str_cmp( buf, "coward"        )) return AFF_FEAR;
    return 0;
}



int affect_name_loc( char* name )
{
    if ( !str_cmp( name, "none"          ) ) return APPLY_NONE;
    if ( !str_cmp( name, "strength"      ) ) return APPLY_STR;
    if ( !str_cmp( name, "dexterity"     ) ) return APPLY_DEX;
    if ( !str_cmp( name, "intelligence"  ) ) return APPLY_INT;
    if ( !str_cmp( name, "wisdom"        ) ) return APPLY_WIS;
    if ( !str_cmp( name, "constitution"  ) ) return APPLY_CON;
    if ( !str_cmp( name, "height"        ) ) return APPLY_HEIGHT;
    if ( !str_cmp( name, "weight"        ) ) return APPLY_WEIGHT;
    if ( !str_cmp( name, "mana"          ) ) return APPLY_MANA;
    if ( !str_cmp( name, "hp"            ) ) return APPLY_HIT;
    if ( !str_cmp( name, "move"          ) ) return APPLY_MOVE;
    if ( !str_cmp( name, "ac"            ) ) return APPLY_AC;
    if ( !str_cmp( name, "hit"           ) ) return APPLY_HITROLL;
    if ( !str_cmp( name, "dam"           ) ) return APPLY_DAMROLL;
    if ( !str_cmp( name, "blood_pool"    ) ) return APPLY_BLOOD_MAX;
    if ( !str_cmp( name, "blood_potency" ) ) return APPLY_BLOOD_POT;
    return APPLY_NONE;
}



int wear_name_loc( char *buf )
{
    if ( !str_cmp( buf, "light" ) )     return WEAR_LIGHT;
    if ( !str_cmp( buf, "lfinger" ) )   return WEAR_FINGER_L;
    if ( !str_cmp( buf, "rfinger" ) )   return WEAR_FINGER_R;
    if ( !str_cmp( buf, "neck1" ) )     return WEAR_NECK_1;
    if ( !str_cmp( buf, "neck2" ) )     return WEAR_NECK_2;
    if ( !str_cmp( buf, "body" ) )      return WEAR_BODY;
    if ( !str_cmp( buf, "head" ) )      return WEAR_HEAD;
    if ( !str_cmp( buf, "legs" ) )      return WEAR_LEGS;
    if ( !str_cmp( buf, "feet" ) )      return WEAR_FEET;
    if ( !str_cmp( buf, "hands" ) )     return WEAR_HANDS;
    if ( !str_cmp( buf, "arms" ) )      return WEAR_ARMS;
    if ( !str_cmp( buf, "about" ) )     return WEAR_ABOUT;
    if ( !str_cmp( buf, "waist" ) )     return WEAR_WAIST;
    if ( !str_cmp( buf, "lwrist" ) )    return WEAR_WRIST_L;
    if ( !str_cmp( buf, "rwrist" ) )    return WEAR_WRIST_R;
    if ( !str_cmp( buf, "hold" ) )      return WEAR_WIELD;
    if ( !str_cmp( buf, "face" ) )      return WEAR_FACE;
    return WEAR_NONE;
}



/*
 * Return ascii name of wear location.
 */
char *wear_loc_name( int wearloc )
{
    switch( wearloc )
    {
               default: return "unknown";
        case WEAR_NONE: return "in the inventory";
       case WEAR_LIGHT: return "as a light";
    case WEAR_FINGER_L: return "on the left finger";
    case WEAR_FINGER_R: return "on the right finger";
      case WEAR_NECK_1: return "around the neck (1)";
      case WEAR_NECK_2: return "around the neck (2)";
        case WEAR_BODY: return "on the body";
        case WEAR_HEAD: return "over the head";
        case WEAR_LEGS: return "on the legs";
        case WEAR_FEET: return "on the feet";
       case WEAR_HANDS: return "on the hands";
        case WEAR_ARMS: return "on the arms";
       case WEAR_ABOUT: return "about the shoulders";
       case WEAR_WAIST: return "around the waist";
     case WEAR_WRIST_L: return "on the left wrist";
     case WEAR_WRIST_R: return "on the right wrist";
       case WEAR_WIELD: return "in the hand";
        case WEAR_FACE: return "on the face";
    }
}



char *act_bit_name( int act )
{
    static char buf[512];

    buf[0] = '\0';
    if ( act & ACT_IS_NPC     ) strcat( buf, " npc"           );
    if ( act & ACT_SENTINEL   ) strcat( buf, " sentinel"      );
    if ( act & ACT_SCAVENGER  ) strcat( buf, " scavenger"     );
    if ( act & ACT_AGGRESSIVE ) strcat( buf, " aggressive"    );
    if ( act & ACT_STAY_AREA  ) strcat( buf, " stay_area"     );
    if ( act & ACT_WIMPY      ) strcat( buf, " wimpy"         );
    if ( act & ACT_PET        ) strcat( buf, " pet"           );
    if ( act & ACT_TRAIN      ) strcat( buf, " trainer"       );
    if ( act & ACT_PRACTICE   ) strcat( buf, " practitioner"  );
    if ( act & ACT_MOUNT      ) strcat( buf, " mount"         );
    if ( act & ACT_NOPARTS    ) strcat( buf, " no_parts"      );
    if ( act & ACT_NOEXP      ) strcat( buf, " no_ext"        );
    if ( act & ACT_SKILLED    ) strcat( buf, " skilled"       );
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}



int get_weapon_type( char *arg )
{
    if (!str_cmp( arg, "hit"	) ) return 0;
    if (!str_cmp( arg, "slice"	) ) return 1;
    if (!str_cmp( arg, "stab"	) ) return 2;
    if (!str_cmp( arg, "slash"	) ) return 3;
    if (!str_cmp( arg, "whip"	) ) return 4;
    if (!str_cmp( arg, "claw"	) ) return 5;
    if (!str_cmp( arg, "blast"	) ) return 6;
    if (!str_cmp( arg, "pound"	) ) return 7;
    if (!str_cmp( arg, "crush"	) ) return 8;
    if (!str_cmp( arg, "grep"	) ) return 9;
    if (!str_cmp( arg, "bite"	) ) return 10;
    if (!str_cmp( arg, "pierce"	) ) return 11;
    if (!str_cmp( arg, "suction") ) return 12;
    if (!str_cmp( arg, "chop"	) ) return 13;
    return 0;
}



/*
 * Use this in dam_message in fight.c if you like.
 */
char * get_type_weapon( int arg )
{
    switch ( arg )
    {
    case 0:  return "hit";
    case 1:  return "slice";
    case 2:  return "stab";
    case 3:  return "slash";
    case 4:  return "whip";
    case 5:  return "claw";
    case 6:  return "blast";
    case 7:  return "pound";
    case 8:  return "crush";
    case 9:  return "grep";
    case 10: return "bite";
    case 11: return "pierce";
    case 12: return "suction";
    case 13: return "chop";
    }

    bug( "Get_type_weapon: unknown type %d.", arg );
    return "(unknown)";
}



int get_container_flags( char *arg )
{
    if (!str_cmp( arg, "closeable"	) ) return 1;
    if (!str_cmp( arg, "pickproof"	) ) return 2;
    if (!str_cmp( arg, "closed"		) ) return 4;
    if (!str_cmp( arg, "locked"		) ) return 8;
    return 0;
}



char * get_flags_container( int arg )
{
    static char buf[512];

    buf[0] = '\0';
    if ( arg & 1 ) strcat( buf, " closeable"	);
    if ( arg & 2 ) strcat( buf, " pickproof"	);
    if ( arg & 4 ) strcat( buf, " closed"	);
    if ( arg & 8 ) strcat( buf, " locked"	);
    return ( buf[0] != '\0' ) ? buf+1 : "none";
}



int get_liquid_type( char *arg )
{
    if (!str_cmp( arg, "water"			) ) return 0;
    if (!str_cmp( arg, "beer"			) ) return 1;
    if (!str_cmp( arg, "wine"			) ) return 2;
    if (!str_cmp( arg, "ale"			) ) return 3;
    if (!str_cmp( arg, "dark_ale"		) ) return 4;
    if (!str_cmp( arg, "whisky"			) ) return 5;
    if (!str_cmp( arg, "lemonade"		) ) return 6;
    if (!str_cmp( arg, "firebreather"		) ) return 7;
    if (!str_cmp( arg, "local_specialty"	) ) return 8;
    if (!str_cmp( arg, "slime_mold_juice"	) ) return 9;
    if (!str_cmp( arg, "milk"			) ) return 10;
    if (!str_cmp( arg, "tea"			) ) return 11;
    if (!str_cmp( arg, "coffee"			) ) return 12;
    if (!str_cmp( arg, "blood"			) ) return 13;
    if (!str_cmp( arg, "salt_water"		) ) return 14;
    if (!str_cmp( arg, "cola"			) ) return 15;
    return 0;
}



char * get_type_liquid( int arg )
{
    switch ( arg )
    {
    case 0:  return "water";
    case 1:  return "beer";
    case 2:  return "wine";
    case 3:  return "ale";
    case 4:  return "dark_ale";
    case 5:  return "whisky";
    case 6:  return "lemonade";
    case 7:  return "firebreather";
    case 8:  return "local_specialty";
    case 9:  return "slime_mold_juice";
    case 10: return "milk";
    case 11: return "tea";
    case 12: return "coffee";
    case 13: return "blood";
    case 14: return "sale_water";
    case 15: return "cola";
    }

    bug( "Get_type_liquid: unknown type %d.", arg );
    return "(unknown)";
}
