/**
 * @file ecu_engine.h
 * @brief Engine Routine header
 *
 * @addtogroup ENGINE
 * @{
 */

#ifndef _ECU_ENGINE_H_
#define _ECU_ENGINE_H_

/**
 * @brief Whether Engine Data from Memory
 */
#define ENGINE_DATA_MEMORY          TRUE

// Engine Tooth Numbering
#define ENGINE_TOOTH_TOP            9
#define ENGINE_TOOTH_BOTTOM         21
#define ENGINE_TOOTH_INTAKE_OPEN    11
#define ENGINE_TOOTH_INTAKE_CLOSE   2
#define ENGINE_TOOTH_COIL_ON        4
#define ENGINE_TOOTH_COIL_OFF       7
#define ENGINE_TOOTH_EXHAUST_OPEN   18
#define ENGINE_TOOTH_EXHAUST_CLOSE  6

/**
 * @brief Amount of all Tooth
 * @details Tooth is 24 with 1 missing
 */
#define ENGINE_ALL_TOOTH    23

/**
 * @brief Degree of each engine tooth
 * @details Simetrically 360/24= 15
 */
#define ENGINE_ALL_DEGREE   15

/**
 * @brief Engine Data Matrix size in memory
 */
#define ENGINE_CDATA        12

void ecu_ENG_InjIgn(void);

#endif

/**  @} */


