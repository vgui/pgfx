#pragma once


enum CanvasWindingRule { nonzero, evenodd };

/*
[GenerateInit]
dictionary ContextAttributes2D {
  // whether or not we're planning to do a lot of readback operations
  boolean willReadFrequently = false;
  // signal if the canvas contains an alpha channel
  boolean alpha = true;
};

dictionary HitRegionOptions {
  Path2D? path = null;
  DOMString id = "";
  Element? control = null;
};

typedef (HTMLImageElement or
         SVGImageElement) HTMLOrSVGImageElement;

typedef (HTMLOrSVGImageElement or
         HTMLCanvasElement or
         HTMLVideoElement or
         OffscreenCanvas or
         ImageBitmap) CanvasImageSource;
*/


struct CanvasRenderingContext2D
{
/*
  // back-reference to the canvas.  Might be null if we're not
  // associated with a canvas.
  readonly attribute HTMLCanvasElement? canvas;

  // Mozilla-specific stuff
  // FIXME Bug 768048 mozCurrentTransform/mozCurrentTransformInverse should return a WebIDL array.
  [Throws]
  attribute object mozCurrentTransform; // [ m11, m12, m21, m22, dx, dy ], i.e. row major
  [Throws]
  attribute object mozCurrentTransformInverse;

  [SetterThrows]
  attribute UTF8String mozTextStyle;

  // image smoothing mode -- if disabled, images won't be smoothed
  // if scaled.
  [Deprecated="PrefixedImageSmoothingEnabled",
   BinaryName="imageSmoothingEnabled"]
  attribute boolean mozImageSmoothingEnabled;

  // Show the caret if appropriate when drawing
  [Func="CanvasUtils::HasDrawWindowPrivilege"]
  const unsigned long DRAWWINDOW_DRAW_CARET   = 0x01;
  // Don't flush pending layout notifications that could otherwise
  // be batched up
  [Func="CanvasUtils::HasDrawWindowPrivilege"]
  const unsigned long DRAWWINDOW_DO_NOT_FLUSH = 0x02;
  // Draw scrollbars and scroll the viewport if they are present
  [Func="CanvasUtils::HasDrawWindowPrivilege"]
  const unsigned long DRAWWINDOW_DRAW_VIEW    = 0x04;
  // Use the widget layer manager if available. This means hardware
  // acceleration may be used, but it might actually be slower or
  // lower quality than normal. It will however more accurately reflect
  // the pixels rendered to the screen.
  [Func="CanvasUtils::HasDrawWindowPrivilege"]
  const unsigned long DRAWWINDOW_USE_WIDGET_LAYERS = 0x08;
  // Don't synchronously decode images - draw what we have
  [Func="CanvasUtils::HasDrawWindowPrivilege"]
  const unsigned long DRAWWINDOW_ASYNC_DECODE_IMAGES = 0x10;
*/
  /**
   * Renders a region of a window into the canvas.  The contents of
   * the window's viewport are rendered, ignoring viewport clipping
   * and scrolling.
   *
   * @param x
   * @param y
   * @param w
   * @param h specify the area of the window to render, in CSS
   * pixels.
   *
   * @param backgroundColor the canvas is filled with this color
   * before we render the window into it. This color may be
   * transparent/translucent. It is given as a CSS color string
   * (e.g., rgb() or rgba()).
   *
   * @param flags Used to better control the drawWindow call.
   * Flags can be ORed together.
   *
   * Of course, the rendering obeys the current scale, transform and
   * globalAlpha values.
   *
   * Hints:
   * -- If 'rgba(0,0,0,0)' is used for the background color, the
   * drawing will be transparent wherever the window is transparent.
   * -- Top-level browsed documents are usually not transparent
   * because the user's background-color preference is applied,
   * but IFRAMEs are transparent if the page doesn't set a background.
   * -- If an opaque color is used for the background color, rendering
   * will be faster because we won't have to compute the window's
   * transparency.
   *
   * This API cannot currently be used by Web content. It is chrome
   * and Web Extensions (with a permission) only.
   */
//  [Throws, NeedsSubjectPrincipal, Func="CanvasUtils::HasDrawWindowPrivilege"]
//  void drawWindow(Window window, double x, double y, double w, double h,
//                  UTF8String bgColor, optional unsigned long flags = 0);


  /**
   * This causes a context that is currently using a hardware-accelerated
   * backend to fallback to a software one. All state should be preserved.
   */
//  [ChromeOnly]
//  void demote();
};

CanvasRenderingContext2D includes CanvasState;
CanvasRenderingContext2D includes CanvasTransform;
CanvasRenderingContext2D includes CanvasCompositing;
CanvasRenderingContext2D includes CanvasImageSmoothing;
CanvasRenderingContext2D includes CanvasFillStrokeStyles;
CanvasRenderingContext2D includes CanvasShadowStyles;
CanvasRenderingContext2D includes CanvasFilters;
CanvasRenderingContext2D includes CanvasRect;
CanvasRenderingContext2D includes CanvasDrawPath;
CanvasRenderingContext2D includes CanvasUserInterface;
CanvasRenderingContext2D includes CanvasText;
CanvasRenderingContext2D includes CanvasDrawImage;
CanvasRenderingContext2D includes CanvasImageData;
CanvasRenderingContext2D includes CanvasPathDrawingStyles;
CanvasRenderingContext2D includes CanvasTextDrawingStyles;
CanvasRenderingContext2D includes CanvasPathMethods;
CanvasRenderingContext2D includes CanvasHitRegions;


struct CanvasState
{
  void save();
  void restore();
};

struct CanvasTransform
{
  void scale(double x, double y);
  void rotate(double angle);
  void translate(double x, double y);
  void transform(double a, double b, double c, double d, double e, double f);

  DOMMatrix getTransform();
  void setTransform(double a, double b, double c, double d, double e, double f);
  void setTransform(optional DOMMatrix2DInit transform = {});
  void resetTransform();
};

struct CanvasCompositing
{
  double globalAlpha {1.0};
  DOMString globalCompositeOperation;
};

struct CanvasImageSmoothing
{
  bool imageSmoothingEnabled;
};

struct CanvasFillStrokeStyles
{
  // colors and styles (see also the CanvasPathDrawingStyles interface)
  (UTF8String or CanvasGradient or CanvasPattern) strokeStyle; // (default black)
  (UTF8String or CanvasGradient or CanvasPattern) fillStyle; // (default black)

  CanvasGradient createLinearGradient(double x0, double y0, double x1, double y1);
  CanvasGradient createRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1);
  CanvasGradient createConicGradient(double angle, double cx, double cy);
  CanvasPattern? createPattern(CanvasImageSource image, DOMString repetition);
};

struct CanvasShadowStyles
{
  double shadowOffsetX; // (default 0)
  double shadowOffsetY; // (default 0)
  double shadowBlur; // (default 0)
  UTF8String shadowColor; // (default transparent black)
};

struct CanvasFilters
{
  UTF8String filter; // (default empty string = no filter)
};

struct CanvasRect {
  void clearRect(double x, double y, double w, double h);
  void fillRect(double x, double y, double w, double h);
  void strokeRect(double x, double y, double w, double h);
};

struct CanvasDrawPath
{
  // path API (see also CanvasPathMethods)
  void beginPath();
  void fill(CanvasWindingRule winding = "nonzero");
  void fill(Path2D path, CanvasWindingRule winding = "nonzero");
  void stroke();
  void stroke(Path2D path);
  void clip(CanvasWindingRule winding = "nonzero");
  void clip(Path2D path, CanvasWindingRule winding = "nonzero");
  void resetClip();
  bool isPointInPath(unrestricted double x, unrestricted double y, CanvasWindingRule winding = "nonzero");
  bool isPointInPath(Path2D path, unrestricted double x, unrestricted double y, CanvasWindingRule winding = "nonzero");
  bool isPointInStroke(double x, double y);
  bool isPointInStroke(Path2D path, unrestricted double x, unrestricted double y);
};

struct CanvasUserInterface
{
  void drawFocusIfNeeded(Element element);
  void scrollPathIntoView();
  void scrollPathIntoView(Path path);
};

struct CanvasText
{
  // text (see also the CanvasPathDrawingStyles interface)
  void fillText(DOMString text, double x, double y, optional double maxWidth);
  void strokeText(DOMString text, double x, double y, optional double maxWidth);
  TextMetrics measureText(DOMString text);
};

struct CanvasDrawImage
{
  void drawImage(CanvasImageSource image, double dx, double dy);
  void drawImage(CanvasImageSource image, double dx, double dy, double dw, double dh);
  void drawImage(CanvasImageSource image, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh);
};

struct CanvasImageData
{
  ImageData createImageData(long sw, long sh);
  ImageData createImageData(ImageData imagedata);
  ImageData getImageData(long sx, long sy, long sw, long sh);
  void putImageData(ImageData imagedata, long dx, long dy);
  void putImageData(ImageData imagedata, long dx, long dy, long dirtyX, long dirtyY, long dirtyWidth, long dirtyHeight);
};

struct CanvasPathDrawingStyles
{
  double lineWidth; // (default 1)
  DOMString lineCap; // "butt", "round", "square" (default "butt")
  DOMString lineJoin; // "round", "bevel", "miter" (default "miter")
  double miterLimit; // (default 10)
  double lineDashOffset;

  void setLineDash(sequence<double> segments);
  sequence<double> getLineDash();
};

struct CanvasTextDrawingStyles
{
  UTF8String font; // (default 10px sans-serif)
  DOMString textAlign; // "start", "end", "left", "right", "center" (default: "start")
  DOMString textBaseline; // "top", "hanging", "middle", "alphabetic", "ideographic", "bottom" (default: "alphabetic")
};

struct CanvasPathMethods
{
  void closePath();
  void moveTo(double x, double y);
  void lineTo(double x, double y);
  void quadraticCurveTo(double cpx, double cpy, double x, double y);
  void bezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
  void arcTo(double x1, double y1, double x2, double y2, double radius);
  void arcTo(double x1, double y1, double x2, double y2, double radiusX, double radiusY, double rotation);
  void rect(double x, double y, double w, double h);
  void arc(double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise = false);
  void ellipse(double x, double y, double radiusX, double radiusY, double rotation, double startAngle, double endAngle, bool anticlockwise = false);
};

struct CanvasHitRegions
{
  void addHitRegion(HitRegionOptions options);
  void removeHitRegion(DOMString id);
  void clearHitRegions();
};

struct CanvasGradient
{
  void addColorStop(float offset, UTF8String color);
};

struct CanvasPattern
{
  void setTransform(DOMMatrix2DInit matrix);
};

struct TextMetrics
{
  double width;
  double actualBoundingBoxLeft;
  double actualBoundingBoxRight;

  double fontBoundingBoxAscent;
  double fontBoundingBoxDescent;

  double actualBoundingBoxAscent;
  double actualBoundingBoxDescent;

  double emHeightAscent;
  double emHeightDescent;

  double hangingBaseline;
  double alphabeticBaseline;
  double ideographicBaseline;
};

struct Path2D
{
  Path2D();
  Path2D(const Path2D& other);
  Path2D(DOMString pathString);

  void addPath(const Path2D& path, optional DOMMatrix2DInit transform = {});
};

Path2D includes CanvasPathMethods;
