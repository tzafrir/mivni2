/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 2                                          */ 
/*                                                                          */ 
/****************************************************************************/

/****************************************************************************/
/*                                                                          */ 
/* File Name : library2.h                                                   */ 
/*                                                                          */ 
/****************************************************************************/

#ifndef _234218_WET2_
#define _234218_WET2_


#ifdef __cplusplus
extern "C" {
#endif




/* Return Values
 * ----------------------------------- */
typedef enum {
	SUCCESS = 0,
	FAILURE = -1,
	INVALID_INPUT = -2

} StatusType;


/* Additional enums
 * ----------------------------------- */
typedef enum {
	NORTH = 0,
	SOUTH = 1
} Shore;



/* Required Interface for the Data Structure
 * -----------------------------------------*/



/* Description:   Initializes a data structure with no towns in it.
 *                ma is the initial monster parameter.
 * Input:         DS - A pointer to the data structure.
 *                ma - Monster attack parameter
 * Output:        None.
 * Return Values: A pointer to a new instance of the data structure - as a void* pointer.
 */
void*       Init(int ma);







/* Description:   Adds a town to the RectangleLand
 * Input:         DS - A pointer to the data structure.
 *                side - The town shore (NORTH/SOUTH)
 *                location - location on the shore: 0 ... infinity
 *                maxNeighborhoods - The maximal number of neighborhoods in this town
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL, location<0 or maxNeighborhoods<0 
 *                FAILURE - In case of any other error 
 *                      examples: town already exists in the given location.
 *                                A border is crossing at the given location
 *                SUCCESS - Otherwise.
 */
StatusType  AddTown(void* DS, Shore side, int location, int maxNeighborhoods);







/* Description:   Add a straight road between two towns.
 *                      The road can cross another road, but cannot cross a border
 * Input:         DS - A pointer to the data structure.
 *                northTown - The location of the north town (integer >= 0)
 *                southTown - The location of the south town (integer >= 0)
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL, or one of the locations <0 
 *                FAILURE - If the road crosses a border or in case of any other error 
 *                SUCCESS - Otherwise.
 */
StatusType  AddRoad(void* DS, int northTown, int southTown);







/* Description:   Removes an existing road between two towns
 * Input:         DS - A pointer to the data structure.
 *                northTown - The location of the north town
 *                southTown - The location of the south town
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL, or one of the locations <0 
 *                FAILURE - In case the towns do not exist, there is no road between them, or any other error 
 *                SUCCESS - Otherwise.
 */
StatusType  RemoveRoad(void* DS, int northTown, int southTown);







/* Description:   Adds a border in the land. The border is a straight line between two points
 * Input:         DS - A pointer to the data structure.
 *                northPt - A point on the north shore
 *                southPt - A point on the south shore
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL, or one of the locations <0 
 *                FAILURE - In case there is a town in one of the locations, the border already exists, 
 *                        the border is going to intersect an existing road/border - 
 *                      - Notice that borders starting/ending at the same point are not considered as intersecting
 *                        if adding this border will result in more borders than towns, or any other error 
 *                SUCCESS - Otherwise.
 */
StatusType  AddBorder(void* DS, int northPt, int southPt);







/* Description:   Removes an existing border
 * Input:         DS - A pointer to the data structure.
 *                northPt - A point on the north shore
 *                southPt - A point on the south shore
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL, or one of the locations <0 
 *                FAILURE - In case this border does not exist, or any other error 
 *                SUCCESS - Otherwise.
 */
StatusType  RemoveBorder(void* DS, int northPt, int southPt);







/* Description:   Add a neighborhood to a given town
 * Input:         DS - A pointer to the data structure.
 *                side - The shore (NORTH/SOUTH) where the town is located
 *                location - The location of the town
 *                population - The population in this new neighborhood
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL, location<0, or population<=0
 *                FAILURE - In case the town does not exist, 
 *                      adding the neighborhood will result in too many neighborhoods in this town,
 *                      or any other error 
 *                SUCCESS - Otherwise.
 */
StatusType  AddNeighborhood(void* DS, Shore side, int location, int population);







/* Description:   Adds many neighborhoods to a given town
 * Input:         DS - A pointer to the data structure.
 *                side - The shore (NORTH/SOUTH) where the town is located
 *                location - The location of the town
 *                size - How many neighborhoods are currently added
 *                populations - An array of populations in each neighborhood. 
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL, location<0, size<=0
 *                        exists i so that population[i]<=0
 *                FAILURE - In case the town does not exist, 
 *                      adding the neighborhoods will result in too many neighborhoods in this town,
 *                      or any other error  
 *                SUCCESS - Otherwise.
 */
StatusType  AddManyNeighborhoods(void* DS, Shore side, int location, int size, const int* populations);







/* Description:   A monster attacks a town. 
 *                It destroys and eats all of the people living in the neighborhood 
 *                which population is the ma'th in its size.
 *                This neighborhood is considered destroyed, and does not exist from then on.
 * Input:         DS - A pointer to the data structure.
 *                side - The shore (NORTH/SOUTH) where the town is located
 *                location - The location of the town
 * Output:        population - The number of people the monster ate
 * Return Values: INVALID_INPUT - If DS==NULL or location<0
 *                FAILURE - In case the town does not exist, there are less than ma neighborhoods in this town, or any other error 
 *                SUCCESS - Otherwise.
 */
StatusType  MonsterAttack(void* DS, Shore side, int location, int* population);







/* Description:   Change the monster "ma" value
 * Input:         DS - A pointer to the data structure.
 *                ma - The new 'ma' value
 * Output:        None.
 * Return Values: INVALID_INPUT - If DS==NULL or ma<=0
 *                FAILURE - Any other error 
 *                SUCCESS - Otherwise.
 */
StatusType  ChangeMa(void* DS, int ma);







/* Description:   Insert Description
 * Input:         DS - A pointer to the data structure.
 * Output:        None.
 * Return Values: None.
 */
void        Quit(void** DS);





#ifdef __cplusplus
}
#endif

#endif    /*_234218_WET2_ */ 

