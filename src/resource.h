#pragma once

/*------------------------
 * Function: 
 * Parameters: 
 * Returns: 
 * Description:
 *     
 *-----------------------*/

/*------------------------
 * Class:
 * Method: 
 * Parameters: 
 * Returns: 
 * Description:
 *     
 *-----------------------*/

/*------------------------
 * Class:
 * Variable: 
 * Description:
 *     
 *-----------------------*/

/*------------------------
 * Class:
 * Operator: 
 * Parameters: 
 * Returns: 
 * Description:
 *     
 *-----------------------*/

/*------------------------
 * Procedure: 
 * Parameters: 
 * Returns: 
 * Description:
 *     
 *-----------------------*/

/*------------------------
 * Class: 
 * Description:
 *     
 *-----------------------*/

/*------------------------
 * Class: 
 * SuperClass: 
 * Description:
 *     
 *-----------------------*/

/*------------------------
 * Enum:  
 * Description:
 *     
 *-----------------------*/

/*------------------------
 * Typedef:  
 * Description:
 *     
 *-----------------------*/

/*------------------------
 * Constant: 
 * Description:
 *     
 *-----------------------*/


/*------------------------
 * Constant: NUM_RESOURCES
 * Description:
 *     The number of resource types
 *     described by the enum
 *     ResourceType
 *-----------------------*/
#define NUM_RESOURCES 5

/*------------------------
 * Enum: ResourceType
 * Description:
 *     Basic resource types.
 *     Intented to be used as indexes
 *     to an array of Resources.
 *-----------------------*/
enum ResourceType
{
    GOLD, JEMS, FOOD, WATER, CLOTH
};

/*------------------------
 * Typedef:  Resource
 * Description:
 *     Represent the quantity of a certain
 *     type of resource.  Resource types
 *     are described in the enum ResourceType
 *-----------------------*/
typedef unsigned int Resource;


