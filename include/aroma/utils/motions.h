/********************************************************************[libaroma]*
 * Copyright (C) 2011-2015 Ahmad Amarullah (http://amarullz.com/)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *______________________________________________________________________________
 *
 * Filename    : motions.h
 * Description : motions interpolator and physics engine
 *
 * + This is part of libaroma, an embedded ui toolkit.
 * + 21/01/15 - Author(s): Ahmad Amarullah
 *
 */
#ifndef __libaroma_aroma_h__
  #error "Include <aroma.h> instead."
#endif
#ifndef __libaroma_motions_h__
#define __libaroma_motions_h__

/******************************************************************************
 * Interpolator                                                               *
 ******************************************************************************/
/*
 * Function    : libaroma_duration_state
 * Return Value: float
 * Descriptions: calculate state by duration
 */
float libaroma_duration_state(long start, int duration);

/*
 * Function    : libaroma_cubic_bezier
 * Return Value: float
 * Descriptions: calculate cubic bezier value from t
 */
float libaroma_cubic_bezier(float x1,float y1,float x2,float y2,float t);
#define libaroma_cubic_bezier_ease(t) \
  libaroma_cubic_bezier(0.25,0.1,0.25,0.1,t)
#define libaroma_cubic_bezier_easein(t) \
  libaroma_cubic_bezier(0.42,0,1,1,t)
#define libaroma_cubic_bezier_easeout(t) \
  libaroma_cubic_bezier(0,0,0.58,1,t)
#define libaroma_cubic_bezier_easeinout(t) \
  libaroma_cubic_bezier(0.42,0,0.58,1,t) 
#define libaroma_cubic_bezier_swiftout(t) \
  libaroma_cubic_bezier(0.4027,0,0.2256,1,t) 
#define libaroma_cubic_bezier_linear(t) (t)

/*
 * Function    : libaroma_motion_fluid
 * Return Value: float
 * Descriptions: fluid motion
 */
float libaroma_motion_fluid(float t);

/*
 * Function    : libaroma_motion_decelerate
 * Return Value: float
 * Descriptions: decelerate motion
 */
float libaroma_motion_decelerate(float t);

/*
 * Function    : libaroma_motion_accelerate
 * Return Value: float
 * Descriptions: accelerate motion
 */
float libaroma_motion_accelerate(float t);

/******************************************************************************
 * Fling Motions                                                              *
 ******************************************************************************/

#define LIBAROMA_FLING_HISTORY 10

/*
 * Struct      : LIBAROMA_FLING
 * Descriptions: fling motion structure
 */
typedef struct{
  int n;
  int points[LIBAROMA_FLING_HISTORY];
  long times[LIBAROMA_FLING_HISTORY];
} LIBAROMA_FLING, *LIBAROMA_FLINGP;

/*
 * Function    : libaroma_fling_down
 * Return Value: void
 * Descriptions: init first fling
 */
void libaroma_fling_down(LIBAROMA_FLINGP p, int pos);

/*
 * Function    : libaroma_fling_move
 * Return Value: void
 * Descriptions: add fling point
 */
void libaroma_fling_move(LIBAROMA_FLINGP p, int pos);

/*
 * Function    : libaroma_fling_up
 * Return Value: int
 * Descriptions: process up event and get velocity
 */
int libaroma_fling_up(LIBAROMA_FLINGP p, int pos);

/******************************************************************************
 * Ripple Motions                                                             *
 ******************************************************************************/
 
#define LIBAROMA_RIPPLE_REDRAW    0x1
#define LIBAROMA_RIPPLE_TOUCHED   0x2
#define LIBAROMA_RIPPLE_HOLDED    0x4
#define LIBAROMA_RIPPLE_RELEASED  0x8
/*
 * Struct      : LIBAROMA_RIPPLE
 * Descriptions: ripple motions structure
 */
typedef struct{
  byte  holded;
  byte  touched;
  float touch_state;
  long  touch_start;
  float release_state;
  long  release_start;
  int   x;
  int   y;
} LIBAROMA_RIPPLE, *LIBAROMA_RIPPLEP;

/*
 * Function    : libaroma_ripple_thread
 * Return Value: byte
 * Descriptions: ripple thread hanlder
 */
byte libaroma_ripple_thread(LIBAROMA_RIPPLEP me, long wait_ms);

/*
 * Function    : libaroma_ripple_down
 * Return Value: void
 * Descriptions: ripple down handler
 */
void libaroma_ripple_down(LIBAROMA_RIPPLEP me, int x, int y);

/*
 * Function    : libaroma_ripple_up
 * Return Value: byte
 * Descriptions: ripple up handler
 */
byte libaroma_ripple_up(LIBAROMA_RIPPLEP me, long wait_ms);

/*
 * Function    : libaroma_ripple_calculation
 * Return Value: byte
 * Descriptions: ripple drawing calculation
 */
static inline byte libaroma_ripple_isactive(LIBAROMA_RIPPLEP me){
  return ((me->touch_state>0)&&(me->release_state<1))?1:0;
}

/*
 * Function    : libaroma_ripple_touched
 * Return Value: byte
 * Descriptions: is ripple touched
 */
static inline byte libaroma_ripple_istouched(LIBAROMA_RIPPLEP me){
  return ((me->touched)?1:0);
}

/*
 * Function    : libaroma_ripple_calculation
 * Return Value: byte
 * Descriptions: ripple drawing calculation
 */
byte libaroma_ripple_calculation(
  LIBAROMA_RIPPLEP me,
  int w, int h,
  bytep push_opacity,
  bytep ripple_opacity,
  int * x, int *y, int * size
);

/*
 * Function    : libaroma_ripple_cancel
 * Return Value: void
 * Descriptions: cancle ripple
 */
void libaroma_ripple_cancel(LIBAROMA_RIPPLEP me);


#endif /* __libaroma_motions_h__ */
