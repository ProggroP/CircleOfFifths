#include "pebble.h"

/* ===========================================================================
 *  CIRCLE OF FIFTHS  -  Trim-Parameter pro Modellklasse
 *  ---------------------------------------------------------------------------
 *  Vier Klassen:
 *    1. eckig alt   -> aplite / basalt / diorite / flint  (144 x 168)  -> #else
 *    2. rund  alt   -> chalk                              (180 x 180)
 *    3. eckig neu   -> emery                              (200 x 228)
 *    4. rund  neu   -> gabbro                             (260 x 260)
 *
 *  Pro Klasse einstellbar:
 *    DUR_R       Radius Dur   (Major-Ring, Pixel ab Mittelpunkt)
 *    MOLL_R      Radius Moll  (minor-Ring, Pixel ab Mittelpunkt)
 *    DUR_FONT    Schriftgroesse Dur   (System-Font, siehe Liste unten)
 *    MOLL_FONT   Schriftgroesse Moll
 *    DUR_DX/DUR_DY    Feinverschiebung Dur-Schrift  (+ = rechts / unten)
 *    MOLL_DX/MOLL_DY  Feinverschiebung Moll-Schrift (+ = rechts / unten)
 *
 *  Verfuegbare System-Schriftgroessen (alle GOTHIC):
 *    FONT_KEY_GOTHIC_14_BOLD
 *    FONT_KEY_GOTHIC_18_BOLD
 *    FONT_KEY_GOTHIC_24_BOLD
 *    FONT_KEY_GOTHIC_28_BOLD
 * ======================================================================== */

#if defined(PBL_PLATFORM_CHALK)
/* -------- 2. RUND ALT  (chalk, 180 x 180) -------- */
  #define MODEL_IS_ROUND 1
  #define MODEL_BIG      0
  #define DIAL_CY        90
  #define TICK_R         86
  #define DUR_R          73
  #define MOLL_R         58
  #define DUR_DX         2
  #define DUR_DY         (-3)
  #define MOLL_DX        2
  #define MOLL_DY        (-2)
  #define DUR_FONT       FONT_KEY_GOTHIC_24_BOLD
  #define MOLL_FONT      FONT_KEY_GOTHIC_18_BOLD
  #define LABEL_MAJOR_DY (-22)
  #define LABEL_MINOR_DY (6)
  #define BATT_Y         56
  #define STEPS_Y        122
  #define INFO_ROW_Y     0     /* nur eckige Modelle */

#elif defined(PBL_PLATFORM_EMERY)
/* -------- 3. ECKIG NEU  (emery, 200 x 228) -------- */
  #define MODEL_IS_ROUND 0
  #define MODEL_BIG      1
  #define DIAL_CY        100
  #define TICK_R         97
  #define DUR_R          82
  #define MOLL_R         60
  #define DUR_DX         3
  #define DUR_DY         (-2)
  #define MOLL_DX        5
  #define MOLL_DY        (-3)
  #define DUR_FONT       FONT_KEY_GOTHIC_28_BOLD
  #define MOLL_FONT      FONT_KEY_GOTHIC_24_BOLD
  #define LABEL_MAJOR_DY (-22)
  #define LABEL_MINOR_DY (6)
  #define BATT_Y         196
  #define STEPS_Y        215
  #define INFO_ROW_Y     214   /* eine Zeile unten: links Batterie, rechts Schritte */

#elif defined(PBL_ROUND)
/* -------- 4. RUND NEU  (gabbro, 260 x 260) -------- */
  #define MODEL_IS_ROUND 1
  #define MODEL_BIG      1
  #define DIAL_CY        130
  #define TICK_R         125
  #define DUR_R          108
  #define MOLL_R         84
  #define DUR_DX         2
  #define DUR_DY         (-2)
  #define MOLL_DX        0
  #define MOLL_DY        (-2)
  #define DUR_FONT       FONT_KEY_GOTHIC_28_BOLD
  #define MOLL_FONT      FONT_KEY_GOTHIC_24_BOLD
  #define LABEL_MAJOR_DY (-25)
  #define LABEL_MINOR_DY (8)
  #define BATT_Y         84
  #define STEPS_Y        175
  #define INFO_ROW_Y     0     /* nur eckige Modelle */

#else
/* -------- 1. ECKIG ALT  (aplite / basalt / diorite / flint, 144 x 168) -------- */
  #define MODEL_IS_ROUND 0
  #define MODEL_BIG      0
  #define DIAL_CY        72
  #define TICK_R         70
  #define DUR_R          60
  #define MOLL_R         46
  #define DUR_DX         3
  #define DUR_DY         1
  #define MOLL_DX        3
  #define MOLL_DY        1
  #define DUR_FONT       FONT_KEY_GOTHIC_18_BOLD
  #define MOLL_FONT      FONT_KEY_GOTHIC_14_BOLD
  #define LABEL_MAJOR_DY (-18)
  #define LABEL_MINOR_DY (4)
  #define BATT_Y         128
  #define STEPS_Y        154
  #define INFO_ROW_Y     156   /* eine Zeile unten: links Batterie, rechts Schritte */
#endif

/* ----- Abgeleitete Zeiger-Laengen (folgen automatisch TICK_R) ----- */
#define HOUR_OUT       (TICK_R * 60 / 95)
#define MIN_OUT        (TICK_R * 80 / 95)
#define HOUR_FILL_OUT  (TICK_R * 55 / 95)
#define MIN_FILL_OUT   (TICK_R * 75 / 95)
#define FILL_IN        (TICK_R * 20 / 95)

#if MODEL_BIG
  #define HAND_W       7
#else
  #define HAND_W       5
#endif

/* ----- Text-Boxen fuer Dur/Moll-Toene ----- */
#if MODEL_BIG
  #define DUR_BOX_W    60
  #define DUR_BOX_H    34
  #define MOLL_BOX_W   52
  #define MOLL_BOX_H   28
#else
  #define DUR_BOX_W    48
  #define DUR_BOX_H    26
  #define MOLL_BOX_W   44
  #define MOLL_BOX_H   22
#endif

/* ----- Info-Elemente (Batterie / Schritte) ----- */
#if MODEL_BIG
  #define INFO_FONT     FONT_KEY_GOTHIC_18_BOLD
  #define INFO_BATT_W   22
  #define INFO_BATT_H   11
  #define INFO_FOOT_W   13
  #define INFO_FOOT_H   17
  #define INFO_GROUP_W  72
  #define INFO_GAP      10
  #define INFO_TEXT_H   24
  #define INFO_TEXT_DY  0
#else
  #define INFO_FONT     FONT_KEY_GOTHIC_14_BOLD
  #define INFO_BATT_W   17
  #define INFO_BATT_H   9
  #define INFO_FOOT_W   10
  #define INFO_FOOT_H   13
  #define INFO_GROUP_W  52
  #define INFO_GAP      8
  #define INFO_TEXT_H   18
  #define INFO_TEXT_DY  0
#endif

/* ----- Persistenz-Schluessel ----- */
#define PKEY_SHOW_BATTERY 1
#define PKEY_SHOW_STEPS   2
#define PKEY_SHORT_HANDS  3

/* ----- Farben ----- */
#define COLOR_BG     GColorWhite
#define COLOR_DUR    GColorBlack
#define COLOR_MOLL   GColorRed
#define COLOR_INFO   GColorBlack

static Window *s_window;
static Layer  *s_hands_layer, *s_dot_layer;

static bool s_show_battery = false;
static bool s_show_steps   = false;
static bool s_short_hands  = false;

static GBitmap *s_steps_bitmap = NULL;

/* =====================================================================
 *  Hilfsfunktionen
 * ===================================================================== */

static GPoint dial_center(GRect bounds) {
#if MODEL_IS_ROUND
  return GPoint(bounds.size.w / 2, bounds.size.h / 2);
#else
  /* Eckige Modelle: nach oben schieben, sobald Batterie ODER Schritte an
   * ist, damit darunter eine Info-Zeile passt. Sonst zentriert. */
  if (s_show_battery || s_show_steps) {
    return GPoint(bounds.size.w / 2, DIAL_CY);
  }
  return GPoint(bounds.size.w / 2, bounds.size.h / 2);
#endif
}

static int get_battery_percent(void) {
  BatteryChargeState s = battery_state_service_peek();
  return s.charge_percent;
}

static int get_steps(void) {
#if defined(PBL_HEALTH)
  time_t start = time_start_of_today();
  time_t end   = time(NULL);
  HealthServiceAccessibilityMask mask =
      health_service_metric_accessible(HealthMetricStepCount, start, end);
  if (mask & HealthServiceAccessibilityMaskAvailable) {
    return (int)health_service_sum_today(HealthMetricStepCount);
  }
  return -1;
#else
  return -1;
#endif
}

/* ----- Gemaltes Batterie-Symbol ----- */
static void draw_battery_icon(GContext *ctx, int x, int y, int w, int h, int pct) {
  graphics_context_set_stroke_color(ctx, COLOR_INFO);
  graphics_context_set_fill_color(ctx, COLOR_INFO);
  graphics_context_set_stroke_width(ctx, 1);

  int body_w = w - 2;
  graphics_draw_rect(ctx, GRect(x, y, body_w, h));

  int nub_h = h / 2;
  if (nub_h < 3) {
    nub_h = 3;
  }
  graphics_fill_rect(ctx, GRect(x + body_w, y + (h - nub_h) / 2, 2, nub_h), 0, GCornerNone);

  int inner_w = body_w - 4;
  if (inner_w < 1) {
    inner_w = 1;
  }
  int fill_w = inner_w * pct / 100;
  if (fill_w < 0) {
    fill_w = 0;
  }
  if (fill_w > inner_w) {
    fill_w = inner_w;
  }
  if (fill_w > 0) {
    graphics_fill_rect(ctx, GRect(x + 2, y + 2, fill_w, h - 4), 0, GCornerNone);
  }
}

/* ----- Gemaltes Schritte-Symbol (Fussabdruck) ----- */
static void draw_foot_icon(GContext *ctx, int x, int y, int w, int h) {
  graphics_context_set_fill_color(ctx, COLOR_INFO);

  int sw = w * 3 / 5;
  if (sw < 4) {
    sw = 4;
  }
  int sx = x + (w - sw) / 2;
  int sole_h = h * 5 / 8;
  graphics_fill_rect(ctx, GRect(sx, y + h - sole_h, sw, sole_h), sw / 2, GCornersAll);

  int tr = (w >= 12) ? 2 : 1;
  graphics_fill_circle(ctx, GPoint(sx + sw / 2 - tr - 1, y + 2 + tr), tr);
  graphics_fill_circle(ctx, GPoint(sx + sw / 2 + 1,      y + tr),     tr);
  graphics_fill_circle(ctx, GPoint(sx + sw / 2 + tr + 3, y + 2 + tr), tr);
}

/* ----- Info-Element Batterie ----- */
static void draw_info_battery(GContext *ctx, int cx, int cy) {
  int left = cx - INFO_GROUP_W / 2;
  int pct  = get_battery_percent();

  draw_battery_icon(ctx, left, cy - INFO_BATT_H / 2, INFO_BATT_W, INFO_BATT_H, pct);

  char buf[8];
  snprintf(buf, sizeof(buf), "%d%%", pct);

  graphics_context_set_text_color(ctx, COLOR_INFO);
  GRect tb = GRect(left + INFO_BATT_W + INFO_GAP,
                   cy - INFO_TEXT_H / 2 + INFO_TEXT_DY,
                   INFO_GROUP_W - INFO_BATT_W - INFO_GAP,
                   INFO_TEXT_H);
  graphics_draw_text(ctx, buf, fonts_get_system_font(INFO_FONT), tb,
                     GTextOverflowModeFill, GTextAlignmentLeft, NULL);
}

/* ----- Info-Element Schritte ----- */
static void draw_info_steps(GContext *ctx, int cx, int cy) {
  int left  = cx - INFO_GROUP_W / 2;
  int steps = get_steps();

  if (s_steps_bitmap) {
    /* Hochgeladene Grafik (Resource-Key STEPS) zentriert im Icon-Feld zeichnen */
    GRect ib = gbitmap_get_bounds(s_steps_bitmap);
    int iw = ib.size.w;
    int ih = ib.size.h;
    GRect dst = GRect(left + (INFO_FOOT_W - iw) / 2,
                      cy - ih / 2,
                      iw, ih);
    graphics_context_set_compositing_mode(ctx, GCompOpSet);
    graphics_draw_bitmap_in_rect(ctx, s_steps_bitmap, dst);
  } else {
    draw_foot_icon(ctx, left, cy - INFO_FOOT_H / 2, INFO_FOOT_W, INFO_FOOT_H);
  }

  char buf[12];
  if (steps < 0) {
    snprintf(buf, sizeof(buf), "--");
  //} else if (steps >= 10000) {
  //  snprintf(buf, sizeof(buf), "%dk", steps / 1000);
  } else {
    snprintf(buf, sizeof(buf), "%d", steps);
  }

  graphics_context_set_text_color(ctx, COLOR_INFO);
  GRect tb = GRect(left + INFO_FOOT_W + INFO_GAP,
                   cy - INFO_TEXT_H / 2 + INFO_TEXT_DY,
                   INFO_GROUP_W - INFO_FOOT_W - INFO_GAP,
                   INFO_TEXT_H);
  graphics_draw_text(ctx, buf, fonts_get_system_font(INFO_FONT), tb,
                     GTextOverflowModeFill, GTextAlignmentRight, NULL);
}

/* =====================================================================
 *  Zeiger
 * ===================================================================== */
static void hands_update_proc(Layer *layer, GContext *ctx) {
  time_t now = time(NULL);
  struct tm *t = localtime(&now);

  int hour = t->tm_hour % 12;
  int min  = t->tm_min;
  int angle;

  GPoint inner, outer;
  int inner_pos, outer_pos;
  GRect bounds  = layer_get_bounds(s_hands_layer);
  GPoint center = dial_center(bounds);

  graphics_context_set_antialiased(ctx, true);

  /* Stundenzeiger */
  angle = DEG_TO_TRIGANGLE((hour * 30) + (min * 5 / 10));
  inner_pos = 0;
  if( s_short_hands) {
    outer_pos = HOUR_OUT/2;
  }
  else {
    outer_pos = HOUR_OUT;
  }  
  graphics_context_set_stroke_width(ctx, HAND_W);
  graphics_context_set_stroke_color(ctx, GColorDarkGray);
  graphics_context_set_fill_color(ctx, GColorDarkGray);
  inner.y = (int16_t)(-cos_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.y;
  inner.x = (int16_t)( sin_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.x;
  outer.y = (int16_t)(-cos_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.y;
  outer.x = (int16_t)( sin_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.x;
  graphics_draw_line(ctx, inner, outer);
  graphics_fill_circle(ctx, center, HAND_W - 1);
  inner_pos = FILL_IN;
  if( s_short_hands) {
    outer_pos = HOUR_FILL_OUT/2;
  }
  else {
    outer_pos = HOUR_FILL_OUT;
  }  
  graphics_context_set_stroke_width(ctx, 1);
  graphics_context_set_stroke_color(ctx, GColorLightGray);
  graphics_context_set_fill_color(ctx, GColorLightGray);
  inner.y = (int16_t)(-cos_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.y;
  inner.x = (int16_t)( sin_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.x;
  outer.y = (int16_t)(-cos_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.y;
  outer.x = (int16_t)( sin_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.x;
  graphics_draw_line(ctx, inner, outer);

  /* Minutenzeiger */
  angle = DEG_TO_TRIGANGLE(min * 6);
  inner_pos = 0;
  if( s_short_hands) {
    outer_pos = MIN_OUT/2;
  }
  else {
    outer_pos = MIN_OUT;
  }  
  graphics_context_set_stroke_width(ctx, HAND_W);
  graphics_context_set_stroke_color(ctx, GColorDarkGray);
  graphics_context_set_fill_color(ctx, GColorDarkGray);
  inner.y = (int16_t)(-cos_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.y;
  inner.x = (int16_t)( sin_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.x;
  outer.y = (int16_t)(-cos_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.y;
  outer.x = (int16_t)( sin_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.x;
  graphics_draw_line(ctx, inner, outer);
  graphics_fill_circle(ctx, center, HAND_W - 1);
  inner_pos = FILL_IN;
  if( s_short_hands) {
    outer_pos = MIN_FILL_OUT/2;
  }
  else {
    outer_pos = MIN_FILL_OUT;
  }  
  graphics_context_set_stroke_width(ctx, 1);
  graphics_context_set_stroke_color(ctx, GColorLightGray);
  graphics_context_set_fill_color(ctx, GColorLightGray);
  inner.y = (int16_t)(-cos_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.y;
  inner.x = (int16_t)( sin_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.x;
  outer.y = (int16_t)(-cos_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.y;
  outer.x = (int16_t)( sin_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.x;
  graphics_draw_line(ctx, inner, outer);

  /* Mittelpunkt */
  graphics_context_set_fill_color(ctx, GColorDarkGray);
  graphics_context_set_stroke_width(ctx, 1);
  graphics_fill_circle(ctx, center, 2);
}

/* =====================================================================
 *  Ziffernblatt + Beschriftung + Info
 * ===================================================================== */
static void dot_update_proc(Layer *layer, GContext *ctx) {
  GRect bounds  = layer_get_bounds(s_dot_layer);
  GPoint center = dial_center(bounds);

  int inner_pos, outer_pos;
  int angle;
  GPoint inner, outer;

  /* Minutenmarken */
  inner_pos = TICK_R;
  outer_pos = TICK_R;
  graphics_context_set_fill_color(ctx, GColorBlack);
  graphics_context_set_stroke_color(ctx, GColorBlack);
  graphics_context_set_stroke_width(ctx, 3);
  for (int i = 0; i < 60; i += 1) {
    angle = DEG_TO_TRIGANGLE(i * 6);
    inner.y = (int16_t)(-cos_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.y;
    inner.x = (int16_t)( sin_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.x;
    outer.y = (int16_t)(-cos_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.y;
    outer.x = (int16_t)( sin_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.x;
    graphics_draw_line(ctx, inner, outer);
  }

  /* Stundenmarken */
  inner_pos = TICK_R;
  outer_pos = TICK_R;
  graphics_context_set_stroke_width(ctx, 5);
  for (int i = 0; i < 12; i += 1) {
    angle = DEG_TO_TRIGANGLE(i * 30);
    inner.y = (int16_t)(-cos_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.y;
    inner.x = (int16_t)( sin_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.x;
    outer.y = (int16_t)(-cos_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.y;
    outer.x = (int16_t)( sin_lookup(angle) * (int32_t)outer_pos / TRIG_MAX_RATIO) + center.x;
    graphics_draw_line(ctx, inner, outer);
  }

  /* Dur-Toene (Major) */
  const char *dur[12] = {
    "C", "G", "D", "A", "E", "B", "F#", "Db", "Ab", "Eb", "Bb", "F"
  };
  graphics_context_set_text_color(ctx, COLOR_DUR);
  inner_pos = DUR_R;
  for (int i = 0; i < 12; i += 1) {
    angle = DEG_TO_TRIGANGLE(i * 30);
    inner.y = (int16_t)(-cos_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.y;
    inner.x = (int16_t)( sin_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.x;
    graphics_draw_text(ctx, dur[i], fonts_get_system_font(DUR_FONT),
                       GRect(inner.x - DUR_BOX_W / 2 + DUR_DX,
                             inner.y - DUR_BOX_H / 2 + DUR_DY,
                             DUR_BOX_W, DUR_BOX_H),
                       GTextOverflowModeFill, GTextAlignmentCenter, NULL);
  }

  /* Moll-Toene (minor) */
  const char *moll[12] = {
    "a", "e", "b", "f#", "c#", "g#", "d#", "bb", "f", "c", "g", "d"
  };
  graphics_context_set_text_color(ctx, COLOR_MOLL);
  inner_pos = MOLL_R;
  for (int i = 0; i < 12; i += 1) {
    angle = DEG_TO_TRIGANGLE(i * 30);
    inner.y = (int16_t)(-cos_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.y;
    inner.x = (int16_t)( sin_lookup(angle) * (int32_t)inner_pos / TRIG_MAX_RATIO) + center.x;
    graphics_draw_text(ctx, moll[i], fonts_get_system_font(MOLL_FONT),
                       GRect(inner.x - MOLL_BOX_W / 2 + MOLL_DX,
                             inner.y - MOLL_BOX_H / 2 + MOLL_DY,
                             MOLL_BOX_W, MOLL_BOX_H),
                       GTextOverflowModeFill, GTextAlignmentCenter, NULL);
  }

  /* Mittel-Beschriftung */
  graphics_context_set_text_color(ctx, COLOR_DUR);
  graphics_draw_text(ctx, "Major", fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD),
                     GRect(0, center.y + LABEL_MAJOR_DY, bounds.size.w, 14),
                     GTextOverflowModeFill, GTextAlignmentCenter, NULL);
  graphics_context_set_text_color(ctx, COLOR_MOLL);
  graphics_draw_text(ctx, "minor", fonts_get_system_font(FONT_KEY_GOTHIC_14_BOLD),
                     GRect(0, center.y + LABEL_MINOR_DY, bounds.size.w, 14),
                     GTextOverflowModeFill, GTextAlignmentCenter, NULL);

  /* Info: Batterie und Schritte */
#if MODEL_IS_ROUND
  /* Runde Modelle: Batterie oben, Schritte unten (unabhaengig schaltbar) */
  int info_cx = bounds.size.w / 2;
  if (s_show_battery) {
    draw_info_battery(ctx, info_cx, BATT_Y);
  }
  if (s_show_steps) {
    draw_info_steps(ctx, info_cx, STEPS_Y);
  }
#else
  /* Eckige Modelle: eine Zeile unten, links Batterie, rechts Schritte.
   * Ist nur eines aktiv, wird es mittig in der Zeile gezeichnet. */
  if (s_show_battery && s_show_steps) {
    draw_info_battery(ctx, bounds.size.w / 4,     INFO_ROW_Y);
    draw_info_steps(ctx,   bounds.size.w * 3 / 4, INFO_ROW_Y);
  } else if (s_show_battery) {
    draw_info_battery(ctx, bounds.size.w / 2, INFO_ROW_Y);
  } else if (s_show_steps) {
    draw_info_steps(ctx, bounds.size.w / 2, INFO_ROW_Y);
  }
#endif
}

/* =====================================================================
 *  Services / Events
 * ===================================================================== */
static void handle_time_tick(struct tm *tick_time, TimeUnits units_changed) {
  layer_mark_dirty(window_get_root_layer(s_window));
}

static void battery_handler(BatteryChargeState charge) {
  layer_mark_dirty(s_dot_layer);
}

static bool tuple_to_bool(Tuple *t) {
  if (!t) {
    return false;
  }
  if (t->length == 1) {
    return t->value->uint8 != 0;
  }
  if (t->length == 2) {
    return t->value->uint16 != 0;
  }
  return t->value->int32 != 0;
}

static void inbox_received(DictionaryIterator *iter, void *context) {
  bool changed = false;

  Tuple *tb = dict_find(iter, MESSAGE_KEY_SHOW_BATTERY);
  if (tb) {
    s_show_battery = tuple_to_bool(tb);
    persist_write_bool(PKEY_SHOW_BATTERY, s_show_battery);
    changed = true;
  }

  Tuple *ts = dict_find(iter, MESSAGE_KEY_SHOW_STEPS);
  if (ts) {
    s_show_steps = tuple_to_bool(ts);
    persist_write_bool(PKEY_SHOW_STEPS, s_show_steps);
    changed = true;
  }

  Tuple *th = dict_find(iter, MESSAGE_KEY_SHORT_HANDS);
  if (th) {
    s_short_hands = tuple_to_bool(th);
    persist_write_bool(PKEY_SHORT_HANDS, s_short_hands);
    changed = true;
  }

  if (changed) {
    layer_mark_dirty(window_get_root_layer(s_window));
  }
}

static void app_focus_changing(bool focusing) {
  if (focusing) {
    layer_set_hidden(window_get_root_layer(s_window), true);
  }
}

static void app_focus_changed(bool focused) {
  if (focused) {
    layer_set_hidden(window_get_root_layer(s_window), false);
    layer_mark_dirty(window_get_root_layer(s_window));
  }
}

static void window_load(Window *window) {
  GRect bounds = layer_get_bounds(window_get_root_layer(s_window));
  window_set_background_color(s_window, COLOR_BG);

  s_steps_bitmap = gbitmap_create_with_resource(RESOURCE_ID_STEPS);

  s_dot_layer = layer_create(bounds);
  layer_set_update_proc(s_dot_layer, dot_update_proc);
  layer_add_child(window_get_root_layer(s_window), s_dot_layer);

  s_hands_layer = layer_create(bounds);
  layer_set_update_proc(s_hands_layer, hands_update_proc);
  layer_add_child(window_get_root_layer(s_window), s_hands_layer);

  app_focus_service_subscribe_handlers((AppFocusHandlers){
    .did_focus  = app_focus_changed,
    .will_focus = app_focus_changing
  });

  tick_timer_service_subscribe(MINUTE_UNIT, handle_time_tick);
  battery_state_service_subscribe(battery_handler);
}

static void window_unload(Window *window) {
  layer_destroy(s_hands_layer);
  layer_destroy(s_dot_layer);
  if (s_steps_bitmap) {
    gbitmap_destroy(s_steps_bitmap);
    s_steps_bitmap = NULL;
  }
}

static void init(void) {
  if (persist_exists(PKEY_SHOW_BATTERY)) {
    s_show_battery = persist_read_bool(PKEY_SHOW_BATTERY);
  }
  if (persist_exists(PKEY_SHOW_STEPS)) {
    s_show_steps = persist_read_bool(PKEY_SHOW_STEPS);
  }
  if (persist_exists(PKEY_SHORT_HANDS)) {
    s_short_hands = persist_read_bool(PKEY_SHORT_HANDS);
  }

  app_message_register_inbox_received(inbox_received);
  app_message_open(64, 64);

  s_window = window_create();
  window_set_window_handlers(s_window, (WindowHandlers){
    .load   = window_load,
    .unload = window_unload,
  });
  window_stack_push(s_window, true);
}

static void deinit(void) {
  battery_state_service_unsubscribe();
  app_focus_service_unsubscribe();
  tick_timer_service_unsubscribe();
  window_destroy(s_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
