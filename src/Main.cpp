#include <math.h>
#include <string>
#include <time.h>

#include "Glut.hpp"

//#include <windows.h> // only used if mouse is required (not portable)
#include "Camera.h"
#include "TexturedPolygons.h"

//--------------------------------------------------------------------------------------

// USE THESE STTEINGS TO CHANGE SPEED (on different spec computers)
// Set speed (steps)
static GLfloat movementSpeed = 10.0f;
static GLfloat rotationSpeed = 0.005f;

// TEXTURE IMAGE AXISES
constexpr GLuint XY      = 0;
constexpr GLuint XZ      = 1;
constexpr GLuint YZ      = 2;
constexpr GLuint YZ_FLIP = 3;
constexpr GLuint XY_FLIP = 4;

// PLAIN TYPES
constexpr GLuint FLAT_PLAIN = 0;
constexpr GLuint XY_PLAIN   = 1;
constexpr GLuint ZY_PLAIN   = 2;

// TEXTURES
// Grass Textures
constexpr GLuint GRASS      = 1;
constexpr GLuint GRASS_2    = 2;
constexpr GLuint GRASS_HILL = 3;
// Pavement Textures
constexpr GLuint PAVEMENT           = 4;
constexpr GLuint PAVEMENT_TOP       = 5;
constexpr GLuint PAVEMENTSIDE_LEFT  = 6;
constexpr GLuint PAVEMENTSIDE_RIGHT = 7;
constexpr GLuint PAVEMENTSIDE_TOP   = 8;
constexpr GLuint PAVEMENT_CORNER_1  = 9;
constexpr GLuint PAVEMENT_CORNER_2  = 10;
constexpr GLuint PAVEMENT_FLIP      = 11;
constexpr GLuint PAVEMENT_TOP_FLIP  = 12;
constexpr GLuint PAVEMENT_16        = 13;
constexpr GLuint DOORPAVE_1         = 14;
// Wall Brick Textures
constexpr GLuint WALL_BRICK_YZ         = 15;
constexpr GLuint WALL_BRICK_XY         = 16;
constexpr GLuint WALL_BRICK_XY_87WIDTH = 17;
constexpr GLuint WALL_BRICK_GAP_YZ     = 18;
constexpr GLuint WALL_BRICK_GAP2_YZ    = 19;
constexpr GLuint WALL_BRICK_USD_YZ     = 20;
constexpr GLuint WALL_BRICK_XY_END     = 21;
constexpr GLuint WALL_BRICK_YZ_END     = 22;
constexpr GLuint WALL_GAP_1            = 23;
constexpr GLuint WALL_BRICK_3_4        = 24;
constexpr GLuint SHADOW_BRICK          = 25;
constexpr GLuint WALL_BRICK_SEC_SIGN   = 216;
// Window Post Textures
constexpr GLuint WINDOWPOST_CHANC_FRONT   = 26;
constexpr GLuint WINDOWPOST_CHANC_RIGHT   = 27;
constexpr GLuint WINDOWPOST_CHANC_LEFT    = 28;
constexpr GLuint WINDOWLEDGE_CHANC_FRONT  = 29;
constexpr GLuint WINDOWLEDGE_CHANC_TOP    = 30;
constexpr GLuint WINDOWPOST_PHYSSCI_FRONT = 31;
constexpr GLuint WINDOWPOST_PHYSSCI_RIGHT = 32;
constexpr GLuint WINDOWPOST_PHYSSCI_LEFT  = 33;
constexpr GLuint WINDOWPOST_LIB_FRONT     = 34;
constexpr GLuint WINDOWPOST_LIB_LEFT      = 35;
constexpr GLuint WINDOWPOST_LIB_RIGHT     = 36;
// Door Post Textures
constexpr GLuint DOOR_POST_SECURITY = 37;
// Window Ledge Textures
constexpr GLuint WINDOWLEDGE_PS_FRONT  = 38;
constexpr GLuint WINDOWLEDGE_PS_TOP    = 39;
constexpr GLuint WINDOWLEDGE_PS_BOTT   = 40;
constexpr GLuint WINDOWLEDGE_LIB_A     = 41;
constexpr GLuint WINDOWLEDGE_LIB_B     = 42;
constexpr GLuint WINDOWLEDGE_LIB_TOP_A = 43;
constexpr GLuint WINDOWLEDGE_LIB_TOP_B = 44;
constexpr GLuint WINDOW_LEDGE_END_1    = 45;
constexpr GLuint WINDOW_LEDGE_END_2    = 46;
// Main Post Textures
constexpr GLuint MAIN_POST   = 47;
constexpr GLuint MAIN_POST_2 = 48;
// Door Post Textures
constexpr GLuint DOOR_POST_CHANC     = 49;
constexpr GLuint DOOR_SIDEPOST_CHANC = 50;
constexpr GLuint DOOR_POST_LIB       = 215;
// Coloured Posts Textures
constexpr GLuint PURPLE_POST     = 51;
constexpr GLuint PURPLE_POSTSIDE = 52;
constexpr GLuint RED_POST        = 53;
constexpr GLuint RED_POSTSIDE    = 54;
// Roof Textures
constexpr GLuint ROOF_TOP        = 55;
constexpr GLuint ROOF_TOP_LIB    = 56;
constexpr GLuint ROOF_PLANKS     = 57;
constexpr GLuint ROOF_BEAM_1     = 58;
constexpr GLuint ROOF_PLANKS_2   = 59;
constexpr GLuint ROOF_BEAM_2     = 60;
constexpr GLuint BELOW_ROOF_FILL = 61;
constexpr GLuint ROOF_BEAM_3     = 62;
constexpr GLuint ROOF_BEAM_4     = 63;
constexpr GLuint ROOF_BEAM_3_TOP = 64;
// KBLT Textures
constexpr GLuint KBLT             = 65;
constexpr GLuint KBLT_EDGE        = 66;
constexpr GLuint KBLT_EDGE_2      = 67;
constexpr GLuint KBLT_EDGE_CORNER = 68;
constexpr GLuint KBLT_SIDE_1      = 69;
constexpr GLuint KBLT_SIDE_2      = 70;
// Sign and Other Textures
constexpr GLuint NEXUS_SIGN         = 71;
constexpr GLuint NEXUS_SIDE         = 72;
constexpr GLuint SECURITY_SIGN      = 73;
constexpr GLuint SECURITY_SIGN_2    = 74;
constexpr GLuint SIGN_1             = 75;
constexpr GLuint SIGN_1_SIDE_1      = 76;
constexpr GLuint SIGN_1_SIDE_2      = 77;
constexpr GLuint SIGN_2             = 78;
constexpr GLuint SIGN_2_SIDE        = 79;
constexpr GLuint PSC_SIGN           = 80;
constexpr GLuint PSC_SIGN_2         = 81;
constexpr GLuint CO_SIGN            = 82;
constexpr GLuint STA_TRAVEL         = 83;
constexpr GLuint STA_TRAVEL_EDGE    = 84;
constexpr GLuint STA_TRAVEL_BRACKET = 85;
constexpr GLuint STA_TRAVEL_2       = 86;
constexpr GLuint STA_TRAVEL_BOTTOM  = 87;
constexpr GLuint TOILET_MEN         = 88;
constexpr GLuint TOILET_WOMEN       = 89;
constexpr GLuint GS_SIGN            = 90;
constexpr GLuint GS_SIGN_2          = 91;
constexpr GLuint GS_SIGN_EDGE       = 92;
constexpr GLuint MAP_2              = 93;
constexpr GLuint GLASS_BOARD        = 94;
constexpr GLuint GLASS_BOARD_2      = 95;
constexpr GLuint GLASS_BOARD_3      = 96;
constexpr GLuint GLASS_B_SIDE       = 97;
constexpr GLuint RUSTY_MAN          = 98;
constexpr GLuint NO_SMOKE_SIGN      = 99;
constexpr GLuint CARPET             = 100;
// Drinks Machine Textures
constexpr GLuint DRINKS_SIDE     = 101;
constexpr GLuint DRINKS_TOP      = 102;
constexpr GLuint DRINKS_EDGE     = 103;
constexpr GLuint DRINKS_SIDE_2   = 104;
constexpr GLuint COKE_MACHINE    = 105;
constexpr GLuint COFFEE_MACHINE  = 106;
constexpr GLuint SWEET_MACHINE   = 107;
constexpr GLuint MACHINE_SIDES   = 108;
constexpr GLuint MACHINE_SIDES_2 = 109;
// Telephone Box Textures
constexpr GLuint TELEPHONE_BACK      = 110;
constexpr GLuint TELEPHONE_FRONT     = 111;
constexpr GLuint TELEPHONE_SIDE_1    = 112;
constexpr GLuint TELEPHONE_FRONT_2   = 113;
constexpr GLuint TELEPHONE_MAIN_SIDE = 114;
constexpr GLuint TELEPHONE_TOP_1     = 115;
constexpr GLuint TELEPHONE_SIDE_2    = 116;
constexpr GLuint TELEPHONE_TOP_2     = 117;
constexpr GLuint TELEPHONE_BOTTOM    = 118;
constexpr GLuint TELEPHONE_FILL      = 119;
constexpr GLuint TELEPHONE_FRONT_3   = 120;
// Step Textures
constexpr GLuint STEPS_LIBRARY     = 121;
constexpr GLuint STEPS_LIBRARY_TOP = 122;
constexpr GLuint STEP_PAVING_1     = 123;
constexpr GLuint STEP_EDGE         = 124;

// Larger Window and Door Textures Etc
constexpr GLuint WINDOW_1          = 125;
constexpr GLuint WINDOW_2          = 126;
constexpr GLuint WINDOW_3          = 127;
constexpr GLuint WINDOW_4          = 128;
constexpr GLuint WINDOW_5          = 129;
constexpr GLuint WINDOW_6          = 130;
constexpr GLuint WINDOW_7          = 131;
constexpr GLuint WINDOW_8          = 132;
constexpr GLuint WINDOW_9          = 133;
constexpr GLuint WINDOW_10         = 134;
constexpr GLuint WINDOW_11         = 135;
constexpr GLuint WINDOW_12         = 136;
constexpr GLuint WINDOW_13         = 137;
constexpr GLuint WINDOW_14         = 138;
constexpr GLuint WINDOW_14B        = 139;
constexpr GLuint WINDOW_15         = 140;
constexpr GLuint WINDOW_16         = 141;
constexpr GLuint WINDOW_17         = 142;
constexpr GLuint WINDOW_2B         = 143;
constexpr GLuint WINDOW_2C         = 144;
constexpr GLuint WINDOW_2US        = 145;
constexpr GLuint WINDOW_3B         = 146;
constexpr GLuint WINDOW_2USB       = 147;
constexpr GLuint WINDOW_LIB_1      = 148;
constexpr GLuint WINDOW_LIB_1A     = 149;
constexpr GLuint WINDOW_LIB_1B     = 150;
constexpr GLuint WINDOW_LIB_1C     = 151;
constexpr GLuint WINDOW_LIB_US_A   = 152;
constexpr GLuint WINDOW_LIB_US_B   = 153;
constexpr GLuint WINDOW_LIB_DOOR_1 = 154;
constexpr GLuint WINDOW_LIB_DOOR_2 = 155;
constexpr GLuint WINDOW_LIB_LONG   = 156;
constexpr GLuint ENTRANCE          = 157;
constexpr GLuint ENTRANCE_2        = 158;
constexpr GLuint EXIT_EAST         = 159;
constexpr GLuint EXIT_WEST         = 220;
constexpr GLuint CHANC_DOOR_1      = 160;
constexpr GLuint CHANC_DOOR_2      = 161;
constexpr GLuint WINDOW_2D         = 162;
constexpr GLuint WINDOW_2E         = 163;
constexpr GLuint WINDOW_1B         = 164;
constexpr GLuint STEP_WINDOW       = 221;

// Above Window Block Textures
constexpr GLuint ABOVE_WINDOW_BLOCK       = 165;
constexpr GLuint ABOVE_WINDOW_BLOCK_2     = 166;
constexpr GLuint ABOVE_WINDOW_BLOCK_3     = 167;
constexpr GLuint ABOVE_WINDOW_EDGE_3B     = 168;
constexpr GLuint ABOVE_WINDOW_BLOCK_XY_3  = 169;
constexpr GLuint ABOVE_LIB                = 170;
constexpr GLuint ABOVE_UNDER_POSTS        = 171;
constexpr GLuint ABOVE_UNDER_POSTS_2      = 172;
constexpr GLuint ABOVE_WINDOW_UNDER_LIB   = 173;
constexpr GLuint ABOVE_WINDOW_BLOCK_CHANC = 174;
constexpr GLuint ABOVE_WINDOW_EDGE_3B_LIB = 175;
constexpr GLuint ABOVE_WINDOW_EDGE_4B_LIB = 176;
constexpr GLuint ABOVE_UNDER_4B           = 177;
constexpr GLuint ABOVE_CHANC_TEXT         = 178;
constexpr GLuint ABOVE_CHANC_TEXT_2       = 179;
constexpr GLuint ABOVE_PHYS_SCI_TEXT      = 180;
constexpr GLuint ABOVE_CHANC_TEXT_3       = 181;
constexpr GLuint ABOVE_LIB_TEXT           = 182;
constexpr GLuint ABOVE_LIB_TEXT_2         = 183;
constexpr GLuint ABOVE_TICKETS_TEXT       = 184;
constexpr GLuint ABOVE_CHANC_EDGE         = 185;
constexpr GLuint TOILET_DOOR_TOP          = 186;
// Light Fitting Textures
constexpr GLuint LIGHT           = 187;
constexpr GLuint LIGHT_SUPPORT   = 188;
constexpr GLuint LIGHT_SUPPORT_2 = 189;
// Bench Textures
constexpr GLuint BENCH_TOP        = 190;
constexpr GLuint BENCH_SIDE       = 191;
constexpr GLuint BENCH_SIDE_2     = 192;
constexpr GLuint BENCH_EDGE       = 193;
constexpr GLuint BENCH_EDGE_TOP   = 194;
constexpr GLuint BENCH_EDGE_SIDE  = 195;
constexpr GLuint BENCH_EDGE_TOP_2 = 196;
constexpr GLuint BENCH_EDGE_2     = 197;
constexpr GLuint BENCH_EDGE_3     = 198;
// Ticket Counter and Ledge Textures
constexpr GLuint TICKET_COUNTER_TOP    = 200;
constexpr GLuint TICKET_COUNTER_EDGE   = 201;
constexpr GLuint TICKET_COUNTER_EDGE_2 = 202;
constexpr GLuint TICKET_COUNTER_EDGE_3 = 203;
constexpr GLuint TICKET_LEDGE          = 204;
constexpr GLuint TICKET_LEDGE_EDGE     = 205;
constexpr GLuint TICKET_LEDGE_EDGE_2   = 206;
// Wall by Steps Textures
constexpr GLuint WALL_BRICK_STEPS_TOP    = 207;
constexpr GLuint WALL_BRICK_STEPS        = 208;
constexpr GLuint WALL_BRICK_STEPS_COVER  = 209;
constexpr GLuint WALL_BRICK_STEPS_EDGE   = 210;
constexpr GLuint WALL_BRICK_STEPS_EDGE_2 = 211;
// Extra Textures
constexpr GLuint DRAINPIPE    = 212;
constexpr GLuint COUNTER_TOP  = 213;
constexpr GLuint COUNTER_SIDE = 214;
// Welcome, Exit and Map Screens
constexpr GLuint MAP     = 217;
constexpr GLuint WELCOME = 218;
constexpr GLuint EXIT    = 219;
constexpr GLuint NO_EXIT = 222;

// 223 Next

//--------------------------------------------------------------------------------------

static GLfloat stepIncrement  = 0.0f;
static GLfloat angleIncrement = 0.0f;
static int frameCount         = 0;
static clock_t lastClock{};

// ratio of screen
static float ratio = 0.0f;
// screen width and height
static int width = 0, height = 0;

// display campus map
static bool DisplayMap = false;
// display welcome screen
static bool DisplayWelcome = true;
// display exit screen
static bool DisplayExit = false;
// display light fittings
static bool lightsOn = false;
// display ECL block
static bool displayECL = true;
// display debug menu
static bool displayDebug = false;
// current fps
static int calcFPS = 0;

// varibles used for tarnslating graphics etc
static GLfloat step       = 0.0f;
static GLfloat step2      = 0.0f;
static GLfloat stepLength = 0.0f;

// Glut Cylinder
static GLUquadricObj *glu_cylinder = nullptr;

// Stores raw image file
static unsigned char *image = nullptr;

// objects
static Camera cam;
static TexturedPolygons tp;

// debug display
void drawDebug();
void calculateFrameRate();

// initializes setting
void myinit();

// display functions
void Display();
void reshape(int w, int h);
void keys(unsigned char key, int x, int y);

// keyboard and mouse functions
void movementKeys(int key, int x, int y);
void releaseKey(int key, int x, int y);
void releaseKeys(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);

// calls display functions below to draw the backdrops
void DrawBackdrop();
// functions to display display lists (images) and bind them to a texture
void DisplayAboveWindowBlock();
void DisplayBench();
void DisplayBricks();
void DisplayChancPosts();
void DisplayCylinders();
void DisplayDoorPaving();
void DisplayDoorPosts();
void DisplayEntranceSteps();
void DisplayExtras();
void DisplayGrass();
void DisplayLargerTextures();
void DisplayLibraryPosts();
void DisplayMainPosts();
void DisplayPavement();
void DisplayPhysSciPosts();
void DisplayPurplePosts();
void DisplayRedPosts();
void DisplayRoof();
void DisplayStepBricks();
void DisplayLights();
void DisplayECL();

// calls functions to create display lists (below)
void CreateTextureList();
// creates display lists
void DrawGrass();
void DrawChancPosts();
void DrawDoorPosts();
void DrawPurplePosts();
void DrawRedPosts();
void DrawMainPosts();
void DrawAboveWindowBlock();
void DrawDoorPaving();
void DrawPhysSciPosts();
void DrawLibraryPosts();
void DrawBricks();
void DrawPavement();
void DrawExtras();
void DrawRoof();
void DrawEntranceSteps();
void DrawLargerTextures();
void DrawLights();
void DrawBench();
void DrawCylinders();
void DrawAngledRoofBeam(GLuint listNo, GLfloat x, GLfloat y, GLfloat z,
                        GLfloat beamSize);
void DrawAngledRoofBeam2(GLuint listNo, GLfloat x, GLfloat y, GLfloat z,
                         GLfloat beamSize);
void DrawStepBricks();
void DrawMapExit();
void DrawECL();

void BindBridgeWall(GLint LR);
void BindBuildingWall();
void BindWallPosts(GLint LR);

void IncrementFrameCount();

// loads images and creates texture
void CreateTextures();
// creates bounding boxes for collsion detection
void CreateBoundingBoxes();
// creates different plains
void CreatePlains();

// deletes image and clears memory
void DeleteImageFromMemory(unsigned char *tempImage);

//--------------------------------------------------------------------------------------
//  Main function
//--------------------------------------------------------------------------------------
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(-1, -1);
    glutInitWindowSize(800, 500);
    glutCreateWindow("Murdoch University Campus Tour");

    myinit();

    glutIgnoreKeyRepeat(1);
    glutSpecialFunc(movementKeys);
    glutSpecialUpFunc(releaseKey);
    glutKeyboardUpFunc(releaseKeys);
    glutKeyboardFunc(keys);

    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutMouseFunc(Mouse);

    // ONLY USE IF REQUIRE MOUSE MOVEMENT
    glutPassiveMotionFunc(mouseMove);

    glutReshapeFunc(reshape);
    glutMainLoop();
    return (0);
}

//--------------------------------------------------------------------------------------
//  Initialize Settings
//--------------------------------------------------------------------------------------
void myinit() {
    // set background (sky colour)
    glClearColor(97.0f / 255.0f, 140.0f / 255.0f, 185.0f / 255.0f, 1.0f);

    // set perpsective
    gluLookAt(0.0, 1.75, 0.0, 0.0, 1.75, -1.0, 0.0, 1.0, 0.0);

    // settings for glut cylinders
    glu_cylinder = gluNewQuadric();
    gluQuadricTexture(glu_cylinder, GL_TRUE);

    // set the world co-ordinates (used to set quadrants for bounding boxes)
    cam.SetWorldCoordinates(36000.0, 43200.0);
    // turn collision detection on
    cam.SetCollisionDetectionOn(true);
    // set number of bounding boxes required
    cam.SetNoBoundingBoxes(19);
    // set starting position of user
    cam.Position(32720.0, 9536.0, 4800.0, 180.0);

    CreatePlains();

    // creates bounding boxes and places in array
    CreateBoundingBoxes();
    // copies bounding boxes from array to linked lists (one fopr each quadrant)
    cam.InitiateBoundingBoxes();

    // load texture images and create display lists
    CreateTextureList();
    CreateTextures();
}

//--------------------------------------------------------------------------------------
//  Main Display Function
//--------------------------------------------------------------------------------------
void Display() {
    // check for movement
    cam.CheckCamera();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // DISPLAY TEXTURES
    // enable texture mapping
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    // displays the welcome screen
    if (DisplayWelcome)
        cam.DisplayWelcomeScreen(width, height, 1, tp.GetTexture(WELCOME));
    // displays the exit screen
    if (DisplayExit)
        cam.DisplayWelcomeScreen(width, height, 0, tp.GetTexture(EXIT));
    // displays the map
    if (DisplayMap)
        cam.DisplayMap(width, height, tp.GetTexture(MAP));
    // display no exit sign (position check should really be in an object, but didn't have time)
    if (((cam.GetLR() > 35500.0f) && (cam.GetFB() < 25344.0f)) ||
        ((cam.GetLR() > 34100.0f) && (cam.GetFB() > 41127.0f))) {
        cam.DisplayNoExit(width, height, tp.GetTexture(NO_EXIT));
    }
    // set the movement and rotation speed according to frame count
    IncrementFrameCount();
    cam.SetMoveSpeed(stepIncrement);
    cam.SetRotateSpeed(angleIncrement);
    // display images
    DrawBackdrop();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    // display debug menu
    if (displayDebug) {
        drawDebug();
        calculateFrameRate();
    }
    // clear buffers
    glutSwapBuffers();
}

//--------------------------------------------------------------------------------------
void reshape(int w, int h) {
    width  = w;
    height = h;
    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0)
        h = 1;
    ratio = 1.0f * w / h;

    // Reset the coordinate system before modifying
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45, static_cast<double>(ratio), 1, 250000);
    glMatrixMode(GL_MODELVIEW);
}

//--------------------------------------------------------------------------------------
// Keyboard Functions
//--------------------------------------------------------------------------------------
void movementKeys(int key, [[maybe_unused]] int x, [[maybe_unused]] int y) {
    switch (key) {
        case GLUT_KEY_LEFT: cam.DirectionLR(-1); break;

        case GLUT_KEY_RIGHT: cam.DirectionLR(1); break;

        case GLUT_KEY_UP: cam.DirectionFB(1); break;

        case GLUT_KEY_DOWN: cam.DirectionFB(-1); break;
    }
}

//--------------------------------------------------------------------------------------
void releaseKey(int key, [[maybe_unused]] int x, [[maybe_unused]] int y) {
    switch (key) {
        // rotate left or right
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT: cam.DirectionLR(0); break;
        // move backwards or forwards
        case GLUT_KEY_UP:
        case GLUT_KEY_DOWN: cam.DirectionFB(0); break;
    }
}

//--------------------------------------------------------------------------------------
void keys(unsigned char key, [[maybe_unused]] int x, [[maybe_unused]] int y) {
    switch (key) {
        // toggle debug menu
        case 'j': displayDebug = (displayDebug == 1) ? 0 : 1; break;
        // step left
        case 'A':
        case 'a': cam.DirectionLR(-5); break;
        // step right
        case 'D':
        case 'd': cam.DirectionLR(5); break;
        // step forward
        case 'W':
        case 'w': cam.DirectionFB(5); break;
        // step backward
        case 'S':
        case 's': cam.DirectionFB(-5); break;
        // display campus map
        case 'm':
        case 'M': {
            if (DisplayMap) {
                DisplayMap = false;
            } else {
                DisplayMap = true;
            }
        } break;
        // exit tour (escape key)
        case 27: {
            cam.SetRotateSpeed(0.0f);
            cam.SetMoveSpeed(0.0f);
            DisplayExit = true;
        } break;
        // display welcome page (space key)
        case ' ': {
            if (DisplayWelcome) {
                cam.SetRotateSpeed(rotationSpeed);
                cam.SetMoveSpeed(movementSpeed);
                DisplayWelcome = false;
            } else {
                cam.SetRotateSpeed(0.0f);
                cam.SetMoveSpeed(0.0f);
                DisplayWelcome = true;
            }
        } break;
        // display light fittings
        case 'l':
        case 'L': {
            if (lightsOn) {
                lightsOn = false;
            } else {
                lightsOn = true;
            }
        } break;

        case 'P':
        case 'p': {
            // Display ECL Block
            if (displayECL) {
                displayECL = false;
            } else {
                displayECL = true;
            }
        } break;
    }
}

//--------------------------------------------------------------------------------------
void releaseKeys(unsigned char key, [[maybe_unused]] int x, [[maybe_unused]] int y) {
    switch (key) {
        // step left or right
        case 'A':
        case 'a':
        case 'D':
        case 'd': cam.DirectionLR(0); break;
        // step forward or back
        case 'W':
        case 'w':
        case 'S':
        case 's': cam.DirectionFB(0); break;
    }
}

/**
 *  @brief Takes in a font and c-style string to print to the openGL window
 *	@param font pointer to OpenGL font to use
 *	@param string c-style string to print to screen
 */
void renderBitmapString(void *font, std::string text) {
    for (char &c : text) {
        glutBitmapCharacter(font, c);
    }
}

/**
 * @brief Draws 3-dimension spatial axis at origin (0,0,0)
 */
void drawAxis() {
    // Positive Z-direction = Red
    glColor3f(255, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100000);
    glEnd();

    // Positive Y-Direction = Green
    glColor3f(0, 255, 0);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100000, 0);
    glEnd();

    // Positive X-Direction = Blue
    glColor3f(0, 0, 255);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(100000, 0, 0);
    glEnd();
}

/**
 * @brief Counts the number of times this function is called in a second to calculate frame rate
 */
void calculateFrameRate() {
    static int frameCounter = 0; // This will store our fps
    static int prevTime     = 0; // This will hold the time from the last frame
    int currentTime         = glutGet(GLUT_ELAPSED_TIME) / 1000;
    ++frameCounter;
    if (currentTime - prevTime > 0) {
        calcFPS      = frameCounter / (currentTime - prevTime);
        frameCounter = 0;
        prevTime     = currentTime;
    }
}
/**
 * @brief Draws the debug menu/ui on screen
 */
void drawDebug() {
    drawAxis();
    glColor3f(1, 1, 1);

    // really shitty way of doing this - probably a better way
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);

    std::string loc = "x: " + std::to_string(cam.GetLR()) +
                      ", y: " + std::to_string(cam.GetUD()) +
                      ", z: " + std::to_string(cam.GetFB()); // coordinates
    std::string fps = "FPS: " + std::to_string(calcFPS);       // fps
    glRasterPos2f(-0.99f, 0.95f); // relative screen location to place text
    renderBitmapString(GLUT_BITMAP_8_BY_13, loc);
    glRasterPos2f(-0.99f, 0.90f); // relative screen location to place text
    renderBitmapString(GLUT_BITMAP_8_BY_13, fps);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
//--------------------------------------------------------------------------------------
//  Mouse Buttons
//--------------------------------------------------------------------------------------
void Mouse(int button, int state, int x, int y) {
    // exit tour if clicked on exit splash screen
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        if ((DisplayExit) && (x <= width / 2.0 + 256.0) &&
            (x >= width / 2.0 - 256.0) && (y <= height / 2.0 + 256.0) &&
            (y >= height / 2.0 - 256.0)) {
            DeleteImageFromMemory(image);
            exit(1);
        }
    }
}

//--------------------------------------------------------------------------------------
//  Mouse Movements (NOT USED)
//  Can be used to rotate around screen using mouse, but keyboard used instead
//--------------------------------------------------------------------------------------
void mouseMove(int x, int y) {
    if (x < 0)
        cam.DirectionRotateLR(0);
    else if (x > width)
        cam.DirectionRotateLR(0);
    else if (x > width / 2.0) {
        cam.DirectionRotateLR(1);
        Display();
        glutWarpPointer(static_cast<int>(width / 2.0),
                        static_cast<int>(height / 2.0));
    } else if (x < width / 2.0) {
        cam.DirectionRotateLR(-1);
        Display();
        glutWarpPointer(static_cast<int>(width / 2.0),
                        static_cast<int>(height / 2.0));
    } else
        cam.DirectionRotateLR(0);
    if (y < 0 || y > height)
        cam.DirectionLookUD(0);

    else if (y > height / 2.0) {
        cam.DirectionLookUD(-1);
        Display();
        glutWarpPointer(static_cast<int>(width / 2.0),
                        static_cast<int>(height / 2.0));
    } else if (y < height / 2.0) {
        cam.DirectionLookUD(1);
        Display();
        glutWarpPointer(static_cast<int>(width / 2.0),
                        static_cast<int>(height / 2.0));
    } else
        cam.DirectionLookUD(0);
}

//--------------------------------------------------------------------------------------
// Set up bounding boxes for collsion detection
//--------------------------------------------------------------------------------------
void CreateBoundingBoxes() {
    // chanc block
    cam.SetAABBMaxX(0, 35879.0);
    cam.SetAABBMinX(0, 33808.0);
    cam.SetAABBMaxZ(0, 22096.0);
    cam.SetAABBMinZ(0, 4688.0);

    // between chanc block and phys sci
    cam.SetAABBMaxX(1, 35999.0);
    cam.SetAABBMinX(1, 35730.0);
    cam.SetAABBMaxZ(1, 25344.0);
    cam.SetAABBMinZ(1, 22096.0);

    // phy sci block panel 1
    cam.SetAABBMaxX(2, 35879.0);
    cam.SetAABBMinX(2, 33808.0);
    cam.SetAABBMaxZ(2, 26752.0);
    cam.SetAABBMinZ(2, 25344.0);

    // phy sci block 1st doorway
    cam.SetAABBMaxX(3, 35879.0);
    cam.SetAABBMinX(3, 34256.0);
    cam.SetAABBMaxZ(3, 27559.0);
    cam.SetAABBMinZ(3, 26752.0);

    // phy sci block 2nd panel
    cam.SetAABBMaxX(4, 35879.0);
    cam.SetAABBMinX(4, 33808.0);
    cam.SetAABBMaxZ(4, 36319.0);
    cam.SetAABBMinZ(4, 27559.0);

    // phy sci block 2nd doorway
    cam.SetAABBMaxX(5, 35879.0);
    cam.SetAABBMinX(5, 34260.0);
    cam.SetAABBMaxZ(5, 37855.0);
    cam.SetAABBMinZ(5, 36319.0);

    // phy sci block 3rd panel
    cam.SetAABBMaxX(6, 35879.0);
    cam.SetAABBMinX(6, 33808.0);
    cam.SetAABBMaxZ(6, 41127.0);
    cam.SetAABBMinZ(6, 37855.0);

    // drinks machine
    cam.SetAABBMaxX(7, 35879.0);
    cam.SetAABBMinX(7, 34704.0);
    cam.SetAABBMaxZ(7, 25344.0);
    cam.SetAABBMinZ(7, 24996.0);

    // bottom of steps
    cam.SetAABBMaxX(8, 33808.0);
    cam.SetAABBMinX(8, 0.0);
    cam.SetAABBMaxZ(8, 4688.0);
    cam.SetAABBMinZ(8, 0.0);

    // end of phy sci block exit (top of steps)
    cam.SetAABBMaxX(9, 35879.0);
    cam.SetAABBMinX(9, 34320.0);
    cam.SetAABBMaxZ(9, 43056.0);
    cam.SetAABBMinZ(9, 41127.0);

    // library end panel
    cam.SetAABBMaxX(10, 34320.0);
    cam.SetAABBMinX(10, 6514.0);
    cam.SetAABBMaxZ(10, 50000.0);
    cam.SetAABBMinZ(10, 43036.0);

    // KBLT
    cam.SetAABBMaxX(11, 28104.0);
    cam.SetAABBMinX(11, 25608.0);
    cam.SetAABBMaxZ(11, 43046.0);
    cam.SetAABBMinZ(11, 42754.0);

    // Canteen block
    cam.SetAABBMaxX(12, 2608.0);
    cam.SetAABBMinX(12, 0.0);
    cam.SetAABBMaxZ(12, 49046.0);
    cam.SetAABBMinZ(12, 0.0);

    // Telephones
    cam.SetAABBMaxX(13, 33892.0);
    cam.SetAABBMinX(13, 33872.0);
    cam.SetAABBMaxZ(13, 25344.0);
    cam.SetAABBMinZ(13, 25173.0);

    // Telephones
    cam.SetAABBMaxX(14, 34277.0);
    cam.SetAABBMinX(14, 34157.0);
    cam.SetAABBMaxZ(14, 25344.0);
    cam.SetAABBMinZ(14, 25173.0);

    // Telephones
    cam.SetAABBMaxX(15, 35462.0);
    cam.SetAABBMinX(15, 34541.0);
    cam.SetAABBMaxZ(15, 25344.0);
    cam.SetAABBMinZ(15, 25173.0);

    // Wall by Steps
    cam.SetAABBMaxX(16, 31548.0);
    cam.SetAABBMinX(16, 31444.0);
    cam.SetAABBMaxZ(16, 10395.0);
    cam.SetAABBMinZ(16, 4590.0);
}

//--------------------------------------------------------------------------------------
// Set up co-ordinates of different plains
//--------------------------------------------------------------------------------------
void CreatePlains() {
    // grass slope
    cam.SetPlains(ZY_PLAIN, 4848.0, 31568.0, 9536.0, 10450.0, 6200.0, 10000.0);

    // flat land (pavement and grass)
    cam.SetPlains(FLAT_PLAIN, 0.0, 36000.0, 10450.0, 10450.0, 10000.0, 17000.0);
    cam.SetPlains(FLAT_PLAIN, 0.0, 6500.0, 10450.0, 10450.0, 17000.0, 40000.0);
    cam.SetPlains(FLAT_PLAIN, 27000.0, 36000.0, 10450.0, 10450.0, 17000.0, 40000.0);
    cam.SetPlains(FLAT_PLAIN, 0.0, 36000.0, 10450.0, 10450.0, 40000.0, 50000.0);

    // top of lower hill
    cam.SetPlains(FLAT_PLAIN, 9000.0, 22000.0, 10650.0, 10650.0, 19000.0, 23000.0);
    cam.SetPlains(FLAT_PLAIN, 9000.0, 10000.0, 10650.0, 10650.0, 28000.0, 33000.0);
    cam.SetPlains(FLAT_PLAIN, 9000.0, 22000.0, 10650.0, 10650.0, 36000.0, 37000.0);
    // sides of lower hill
    cam.SetPlains(ZY_PLAIN, 6500.0, 27000.0, 10450.0, 10650.0, 17000.0, 19000.0);
    cam.SetPlains(ZY_PLAIN, 6500.0, 27000.0, 10650.0, 10450.0, 37000.0, 40000.0);
    cam.SetPlains(XY_PLAIN, 6500.0, 9000.0, 10450.0, 10650.0, 17000.0, 40000.0);
    cam.SetPlains(XY_PLAIN, 22000.0, 27000.0, 10650.0, 10450.0, 17000.0, 40000.0);

    // top of higher hill
    cam.SetPlains(FLAT_PLAIN, 14000.0, 18000.0, 10875.0, 108075.0, 28000.0, 33000.0);
    // sides of higher hill
    cam.SetPlains(ZY_PLAIN, 10000.0, 22000.0, 10650.0, 10875.0, 23000.0, 28000.0);
    cam.SetPlains(ZY_PLAIN, 10000.0, 22000.0, 10875.0, 10650.0, 33000.0, 36000.0);
    cam.SetPlains(XY_PLAIN, 10000.0, 14000.0, 10650.0, 10875.0, 23000.0, 36000.0);
    cam.SetPlains(XY_PLAIN, 18000.0, 22000.0, 10875.0, 10650.0, 23000.0, 36000.0);

    // entance steps
    step       = 10450.0f;
    stepLength = 9808.0f;
    for (int i = 0; i < 18; i++) {
        cam.SetPlains(FLAT_PLAIN, 31582.0, 33835, step, step, stepLength,
                      stepLength + 42.0f);
        step -= 48.0f;
        stepLength -= 142.0f;
        if ((i + 3) % 5 == 0) {
            stepLength -= 500.0f;
            step -= 48.0f;
        }
    }

    // temp plain to take down to ECL1
    cam.SetPlains(ZY_PLAIN, 3200.0, 4800.0, 10450.0, 9370.0, 53400.0, 57900.0);
}

//--------------------------------------------------------------------------------------
//  Delete raw image and clear memory
//--------------------------------------------------------------------------------------
void DeleteImageFromMemory(unsigned char *tempImage) {
    delete tempImage;
}

//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
// Load and Create Textures
//--------------------------------------------------------------------------------------
void CreateTextures() {
    glEnable(GL_DEPTH_TEST);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // set texture count
    tp.SetTextureCount(250);

    // load and create textures
    image = tp.LoadTexture("res/tex/abovechanctext.raw", 128, 1024);
    tp.CreateTexture(ABOVE_CHANC_TEXT, image, 128, 1024);

    image = tp.LoadTexture("res/tex/abovechanctext2.raw", 128, 1024);
    tp.CreateTexture(ABOVE_CHANC_TEXT_2, image, 128, 1024);

    image = tp.LoadTexture("res/tex/abovechanctext3.raw", 128, 1024);
    tp.CreateTexture(ABOVE_CHANC_TEXT_3, image, 128, 1024);

    image = tp.LoadTexture("res/tex/abovelibtext.raw", 1024, 256);
    tp.CreateTexture(ABOVE_LIB_TEXT, image, 1024, 256);

    image = tp.LoadTexture("res/tex/abovelibrarytext2.raw", 1024, 256);
    tp.CreateTexture(ABOVE_LIB_TEXT_2, image, 1024, 256);

    image = tp.LoadTexture("res/tex/aboveunder4b.raw", 256, 128);
    tp.CreateTexture(ABOVE_UNDER_4B, image, 256, 128);

    image = tp.LoadTexture("res/tex/abovewindows.raw", 128, 256);
    tp.CreateTexture(ABOVE_WINDOW_BLOCK, image, 128, 256);

    image = tp.LoadTexture("res/tex/abovewindows2.raw", 128, 256);
    tp.CreateTexture(ABOVE_WINDOW_BLOCK_2, image, 128, 256);

    image = tp.LoadTexture("res/tex/abovewindowschanc.raw", 128, 256);
    tp.CreateTexture(ABOVE_WINDOW_BLOCK_CHANC, image, 128, 256);

    image = tp.LoadTexture("res/tex/abovewindows2posts.raw", 128, 256);
    tp.CreateTexture(ABOVE_UNDER_POSTS, image, 128, 256);

    image = tp.LoadTexture("res/tex/abovewindows2posts2.raw", 128, 256);
    tp.CreateTexture(ABOVE_UNDER_POSTS_2, image, 256, 128);

    image = tp.LoadTexture("res/tex/abovewindowslib.raw", 256, 256);
    tp.CreateTexture(ABOVE_LIB, image, 256, 256);

    image = tp.LoadTexture("res/tex/abovewindows2lib.raw", 256, 128);
    tp.CreateTexture(ABOVE_WINDOW_UNDER_LIB, image, 256, 128);

    image = tp.LoadTexture("res/tex/abovewindows3bricks.raw", 256, 256);
    tp.CreateTexture(ABOVE_WINDOW_BLOCK_3, image, 256, 256);

    image = tp.LoadTexture("res/tex/abovephysscitext.raw", 256, 1024);
    tp.CreateTexture(ABOVE_PHYS_SCI_TEXT, image, 256, 1024);

    image = tp.LoadTexture("res/tex/abovewindows3bricksxy.raw", 256, 256);
    tp.CreateTexture(ABOVE_WINDOW_BLOCK_XY_3, image, 256, 256);

    image = tp.LoadTexture("res/tex/abovewindowedge.raw", 128, 256);
    tp.CreateTexture(ABOVE_WINDOW_EDGE_3B, image, 128, 256);

    image = tp.LoadTexture("res/tex/abovewindowedgelib.raw", 256, 64);
    tp.CreateTexture(ABOVE_WINDOW_EDGE_3B_LIB, image, 256, 64);

    image = tp.LoadTexture("res/tex/abovewindowslibedge.raw", 256, 64);
    tp.CreateTexture(ABOVE_WINDOW_EDGE_4B_LIB, image, 256, 64);

    image = tp.LoadTexture("res/tex/aboveticketstext.raw", 256, 256);
    tp.CreateTexture(ABOVE_TICKETS_TEXT, image, 256, 256);

    image = tp.LoadTexture("res/tex/abovewindowsedge.raw", 128, 128);
    tp.CreateTexture(ABOVE_CHANC_EDGE, image, 128, 128);

    image = tp.LoadTexture("res/tex/belowrooffill.raw", 128, 256);
    tp.CreateTexture(BELOW_ROOF_FILL, image, 128, 256);

    image = tp.LoadTexture("res/tex/bench.raw", 64, 64);
    tp.CreateTexture(BENCH_TOP, image, 64, 64);

    image = tp.LoadTexture("res/tex/benchedgeside.raw", 64, 64);
    tp.CreateTexture(BENCH_EDGE_SIDE, image, 64, 64);

    image = tp.LoadTexture("res/tex/benchedge.raw", 64, 64);
    tp.CreateTexture(BENCH_EDGE, image, 64, 64);

    image = tp.LoadTexture("res/tex/benchedgetop.raw", 64, 64);
    tp.CreateTexture(BENCH_EDGE_TOP, image, 64, 64);

    image = tp.LoadTexture("res/tex/benchedge2.raw", 64, 64);
    tp.CreateTexture(BENCH_EDGE_2, image, 64, 64);

    image = tp.LoadTexture("res/tex/benchedge3.raw", 64, 64);
    tp.CreateTexture(BENCH_EDGE_3, image, 64, 64);

    image = tp.LoadTexture("res/tex/benchedgetop2.raw", 64, 64);
    tp.CreateTexture(BENCH_EDGE_TOP_2, image, 64, 64);

    image = tp.LoadTexture("res/tex/benchside.raw", 64, 64);
    tp.CreateTexture(BENCH_SIDE, image, 64, 64);

    image = tp.LoadTexture("res/tex/benchside2.raw", 64, 64);
    tp.CreateTexture(BENCH_SIDE_2, image, 64, 64);

    image = tp.LoadTexture("res/tex/bricks1.raw", 128, 128);
    tp.CreateTexture(WALL_BRICK_YZ, image, 128, 128);

    image = tp.LoadTexture("res/tex/bricks2.raw", 128, 128);
    tp.CreateTexture(WALL_BRICK_XY, image, 128, 128);

    image = tp.LoadTexture("res/tex/bricks2edge.raw", 128, 128);
    tp.CreateTexture(WALL_BRICK_XY_END, image, 128, 128);

    image = tp.LoadTexture("res/tex/bricks1edge.raw", 128, 128);
    tp.CreateTexture(WALL_BRICK_YZ_END, image, 128, 128);

    image = tp.LoadTexture("res/tex/bricks075.raw", 128, 128);
    tp.CreateTexture(WALL_BRICK_3_4, image, 128, 128);

    image = tp.LoadTexture("res/tex/brick87.raw", 128, 128);
    tp.CreateTexture(WALL_BRICK_XY_87WIDTH, image, 128, 128);

    image = tp.LoadTexture("res/tex/brickgap.raw", 128, 32);
    tp.CreateTexture(WALL_BRICK_GAP_YZ, image, 128, 32);

    image = tp.LoadTexture("res/tex/brickgap2.raw", 128, 32);
    tp.CreateTexture(WALL_BRICK_GAP2_YZ, image, 128, 32);

    image = tp.LoadTexture("res/tex/bricksecsign.raw", 256, 128);
    tp.CreateTexture(WALL_BRICK_SEC_SIGN, image, 256, 128);

    image = tp.LoadTexture("res/tex/brickshadow.raw", 128, 128);
    tp.CreateTexture(SHADOW_BRICK, image, 128, 128);

    image = tp.LoadTexture("res/tex/bricksusd.raw", 128, 128);
    tp.CreateTexture(WALL_BRICK_USD_YZ, image, 128, 128);

    image = tp.LoadTexture("res/tex/carpet.raw", 32, 32);
    tp.CreateTexture(CARPET, image, 32, 32);

    image = tp.LoadTexture("res/tex/coffeemachine.raw", 128, 256);
    tp.CreateTexture(COFFEE_MACHINE, image, 128, 256);

    image = tp.LoadTexture("res/tex/cokemachine.raw", 128, 256);
    tp.CreateTexture(COKE_MACHINE, image, 128, 256);

    image = tp.LoadTexture("res/tex/cosign.raw", 256, 128);
    tp.CreateTexture(CO_SIGN, image, 256, 128);

    image = tp.LoadTexture("res/tex/counterside.raw", 4, 16);
    tp.CreateTexture(COUNTER_SIDE, image, 4, 16);

    image = tp.LoadTexture("res/tex/countertop.raw", 1, 1);
    tp.CreateTexture(COUNTER_TOP, image, 1, 1);

    image = tp.LoadTexture("res/tex/drainpipe.raw", 32, 2);
    tp.CreateTexture(DRAINPIPE, image, 32, 2);

    image = tp.LoadTexture("res/tex/drinksedge.raw", 16, 2);
    tp.CreateTexture(DRINKS_EDGE, image, 16, 2);

    image = tp.LoadTexture("res/tex/drinksside.raw", 64, 64);
    tp.CreateTexture(DRINKS_SIDE, image, 64, 64);

    image = tp.LoadTexture("res/tex/drinksside2.raw", 64, 64);
    tp.CreateTexture(DRINKS_SIDE_2, image, 64, 64);

    image = tp.LoadTexture("res/tex/drinkssidetop.raw", 64, 64);
    tp.CreateTexture(DRINKS_TOP, image, 64, 64);

    image = tp.LoadTexture("res/tex/doorpave1.raw", 128, 256);
    tp.CreateTexture(DOORPAVE_1, image, 128, 256);

    image = tp.LoadTexture("res/tex/doorpost1.raw", 1024, 128);
    tp.CreateTexture(DOOR_POST_CHANC, image, 1024, 128);

    image = tp.LoadTexture("res/tex/doorpostsec.raw", 1024, 128);
    tp.CreateTexture(DOOR_POST_SECURITY, image, 1024, 128);

    image = tp.LoadTexture("res/tex/doorpostside1.raw", 64, 1024);
    tp.CreateTexture(DOOR_SIDEPOST_CHANC, image, 64, 1024);

    image = tp.LoadTexture("res/tex/doorpostlibside.raw", 512, 64);
    tp.CreateTexture(DOOR_POST_LIB, image, 512, 64);

    image = tp.LoadTexture("res/tex/glassboard.raw", 512, 256);
    tp.CreateTexture(GLASS_BOARD, image, 512, 256);

    image = tp.LoadTexture("res/tex/glassboard2.raw", 512, 256);
    tp.CreateTexture(GLASS_BOARD_2, image, 512, 256);

    image = tp.LoadTexture("res/tex/glassboard3.raw", 512, 256);
    tp.CreateTexture(GLASS_BOARD_3, image, 512, 256);

    image = tp.LoadTexture("res/tex/glassboardside.raw", 2, 16);
    tp.CreateTexture(GLASS_B_SIDE, image, 2, 16);

    image = tp.LoadTexture("res/tex/grass.raw", 64, 64);
    tp.CreateTexture(GRASS, image, 64, 64);

    image = tp.LoadTexture("res/tex/grass2.raw", 64, 64);
    tp.CreateTexture(GRASS_2, image, 64, 64);

    image = tp.LoadTexture("res/tex/grass3.raw", 64, 64);
    tp.CreateTexture(GRASS_HILL, image, 64, 64);

    image = tp.LoadTexture("res/tex/gssign.raw", 256, 256);
    tp.CreateTexture(GS_SIGN, image, 256, 256);

    image = tp.LoadTexture("res/tex/gssign2.raw", 256, 256);
    tp.CreateTexture(GS_SIGN_2, image, 256, 256);

    image = tp.LoadTexture("res/tex/gssignedge.raw", 256, 64);
    tp.CreateTexture(GS_SIGN_EDGE, image, 256, 64);

    image = tp.LoadTexture("res/tex/kbl.raw", 512, 256);
    tp.CreateTexture(KBLT, image, 512, 256);

    image = tp.LoadTexture("res/tex/kbltside1.raw", 2, 128);
    tp.CreateTexture(KBLT_SIDE_1, image, 2, 128);

    image = tp.LoadTexture("res/tex/kbltside2.raw", 2, 2);
    tp.CreateTexture(KBLT_SIDE_2, image, 2, 2);

    image = tp.LoadTexture("res/tex/kblcorner.raw", 1, 1);
    tp.CreateTexture(KBLT_EDGE_CORNER, image, 1, 1);

    image = tp.LoadTexture("res/tex/kbltedge.raw", 16, 32);
    tp.CreateTexture(KBLT_EDGE, image, 16, 32);

    image = tp.LoadTexture("res/tex/kbltedge2.raw", 32, 16);
    tp.CreateTexture(KBLT_EDGE_2, image, 32, 16);

    image = tp.LoadTexture("res/tex/light.raw", 256, 64);
    tp.CreateTexture(LIGHT, image, 256, 64);

    image = tp.LoadTexture("res/tex/lightsupport.raw", 8, 2);
    tp.CreateTexture(LIGHT_SUPPORT, image, 8, 2);

    image = tp.LoadTexture("res/tex/lightsupport2.raw", 2, 8);
    tp.CreateTexture(LIGHT_SUPPORT_2, image, 2, 8);

    image = tp.LoadTexture("res/tex/machinesides.raw", 1, 1);
    tp.CreateTexture(MACHINE_SIDES, image, 1, 1);

    image = tp.LoadTexture("res/tex/machinesides2.raw", 1, 1);
    tp.CreateTexture(MACHINE_SIDES_2, image, 1, 1);

    image = tp.LoadTexture("res/tex/mainpost.raw", 128, 256);
    tp.CreateTexture(MAIN_POST, image, 128, 256);

    image = tp.LoadTexture("res/tex/mainpost2.raw", 256, 128);
    tp.CreateTexture(MAIN_POST_2, image, 256, 128);

    image = tp.LoadTexture("res/tex/map2.raw", 256, 512);
    tp.CreateTexture(MAP_2, image, 256, 512);

    image = tp.LoadTexture("res/tex/nexus.raw", 512, 256);
    tp.CreateTexture(NEXUS_SIGN, image, 512, 256);

    image = tp.LoadTexture("res/tex/nexusside.raw", 2, 16);
    tp.CreateTexture(NEXUS_SIDE, image, 2, 16);

    image = tp.LoadTexture("res/tex/noexit.raw", 256, 64);
    tp.CreateTexture(NO_EXIT, image, 256, 64);

    image = tp.LoadTexture("res/tex/nosmokesign.raw", 256, 128);
    tp.CreateTexture(NO_SMOKE_SIGN, image, 256, 128);

    image = tp.LoadTexture("res/tex/pavement.raw", 128, 64);
    tp.CreateTexture(PAVEMENT, image, 128, 64);

    image = tp.LoadTexture("res/tex/pavement16.raw", 32, 64);
    tp.CreateTexture(PAVEMENT_16, image, 32, 64);

    image = tp.LoadTexture("res/tex/pavementflip.raw", 128, 64);
    tp.CreateTexture(PAVEMENT_FLIP, image, 128, 64);

    image = tp.LoadTexture("res/tex/pavementcorner1.raw", 128, 128);
    tp.CreateTexture(PAVEMENT_CORNER_1, image, 128, 128);

    image = tp.LoadTexture("res/tex/pavementcorner2.raw", 128, 128);
    tp.CreateTexture(PAVEMENT_CORNER_2, image, 128, 128);

    image = tp.LoadTexture("res/tex/pavementtop.raw", 64, 128);
    tp.CreateTexture(PAVEMENT_TOP, image, 64, 128);

    image = tp.LoadTexture("res/tex/pavementtopflip.raw", 64, 128);
    tp.CreateTexture(PAVEMENT_TOP_FLIP, image, 64, 128);

    image = tp.LoadTexture("res/tex/pavementside.raw", 64, 64);
    tp.CreateTexture(PAVEMENTSIDE_LEFT, image, 64, 64);

    image = tp.LoadTexture("res/tex/pavementside2.raw", 64, 64);
    tp.CreateTexture(PAVEMENTSIDE_RIGHT, image, 64, 64);

    image = tp.LoadTexture("res/tex/pavementside3.raw", 64, 64);
    tp.CreateTexture(PAVEMENTSIDE_TOP, image, 64, 64);

    image = tp.LoadTexture("res/tex/phonefront.raw", 512, 32);
    tp.CreateTexture(TELEPHONE_FRONT, image, 512, 32);

    image = tp.LoadTexture("res/tex/phoneside1.raw", 32, 256);
    tp.CreateTexture(TELEPHONE_SIDE_1, image, 32, 256);

    image = tp.LoadTexture("res/tex/phonefront2.raw", 512, 16);
    tp.CreateTexture(TELEPHONE_FRONT_2, image, 512, 16);

    image = tp.LoadTexture("res/tex/phonemainside.raw", 512, 256);
    tp.CreateTexture(TELEPHONE_MAIN_SIDE, image, 512, 256);

    image = tp.LoadTexture("res/tex/phonetop1.raw", 512, 128);
    tp.CreateTexture(TELEPHONE_TOP_1, image, 512, 128);

    image = tp.LoadTexture("res/tex/phoneside2.raw", 16, 256);
    tp.CreateTexture(TELEPHONE_SIDE_2, image, 16, 256);

    image = tp.LoadTexture("res/tex/phonetop2.raw", 128, 256);
    tp.CreateTexture(TELEPHONE_TOP_2, image, 128, 256);

    image = tp.LoadTexture("res/tex/phonebottom.raw", 512, 128);
    tp.CreateTexture(TELEPHONE_BOTTOM, image, 512, 128);

    image = tp.LoadTexture("res/tex/phonefill.raw", 2, 2);
    tp.CreateTexture(TELEPHONE_FILL, image, 2, 2);

    image = tp.LoadTexture("res/tex/phonefront3.raw", 16, 512);
    tp.CreateTexture(TELEPHONE_FRONT_3, image, 16, 512);

    image = tp.LoadTexture("res/tex/pscsign.raw", 256, 128);
    tp.CreateTexture(PSC_SIGN, image, 256, 128);

    image = tp.LoadTexture("res/tex/pscsign2.raw", 256, 128);
    tp.CreateTexture(PSC_SIGN_2, image, 256, 128);

    image = tp.LoadTexture("res/tex/purplepost.raw", 64, 128);
    tp.CreateTexture(PURPLE_POST, image, 64, 128);

    image = tp.LoadTexture("res/tex/purplepostside.raw", 128, 64);
    tp.CreateTexture(PURPLE_POSTSIDE, image, 128, 64);

    image = tp.LoadTexture("res/tex/redpost.raw", 64, 128);
    tp.CreateTexture(RED_POST, image, 64, 128);

    image = tp.LoadTexture("res/tex/redpostside.raw", 64, 64);
    tp.CreateTexture(RED_POSTSIDE, image, 64, 64);

    image = tp.LoadTexture("res/tex/roofbeam1.raw", 128, 32);
    tp.CreateTexture(ROOF_BEAM_1, image, 128, 32);

    image = tp.LoadTexture("res/tex/roofbeam2.raw", 32, 128);
    tp.CreateTexture(ROOF_BEAM_2, image, 32, 128);

    image = tp.LoadTexture("res/tex/roofbeam3.raw", 64, 128);
    tp.CreateTexture(ROOF_BEAM_3, image, 64, 128);

    image = tp.LoadTexture("res/tex/roofbeam3top.raw", 128, 128);
    tp.CreateTexture(ROOF_BEAM_3_TOP, image, 128, 128);

    image = tp.LoadTexture("res/tex/roofbeam4.raw", 128, 64);
    tp.CreateTexture(ROOF_BEAM_4, image, 128, 64);

    image = tp.LoadTexture("res/tex/roofplanks.raw", 128, 128);
    tp.CreateTexture(ROOF_PLANKS, image, 128, 128);

    image = tp.LoadTexture("res/tex/roofplanks2.raw", 128, 128);
    tp.CreateTexture(ROOF_PLANKS_2, image, 128, 128);

    image = tp.LoadTexture("res/tex/rooftop.raw", 2, 128);
    tp.CreateTexture(ROOF_TOP, image, 2, 128);

    image = tp.LoadTexture("res/tex/rooftoplib.raw", 128, 2);
    tp.CreateTexture(ROOF_TOP_LIB, image, 128, 2);

    image = tp.LoadTexture("res/tex/rustyman.raw", 256, 1024);
    tp.CreateTexture(RUSTY_MAN, image, 256, 1024);

    image = tp.LoadTexture("res/tex/securitysign1.raw", 128, 128);
    tp.CreateTexture(SECURITY_SIGN, image, 128, 128);

    image = tp.LoadTexture("res/tex/securitysign2.raw", 128, 128);
    tp.CreateTexture(SECURITY_SIGN_2, image, 128, 128);

    image = tp.LoadTexture("res/tex/sign1.raw", 512, 256);
    tp.CreateTexture(SIGN_1, image, 512, 256);

    image = tp.LoadTexture("res/tex/sign1side1.raw", 16, 512);
    tp.CreateTexture(SIGN_1_SIDE_1, image, 16, 512);

    image = tp.LoadTexture("res/tex/sign1side2.raw", 16, 512);
    tp.CreateTexture(SIGN_1_SIDE_2, image, 16, 512);

    image = tp.LoadTexture("res/tex/sign2.raw", 512, 512);
    tp.CreateTexture(SIGN_2, image, 512, 512);

    image = tp.LoadTexture("res/tex/sign2side.raw", 512, 16);
    tp.CreateTexture(SIGN_2_SIDE, image, 512, 16);

    image = tp.LoadTexture("res/tex/statravel.raw", 256, 256);
    tp.CreateTexture(STA_TRAVEL, image, 256, 256);

    image = tp.LoadTexture("res/tex/statraveledge.raw", 256, 64);
    tp.CreateTexture(STA_TRAVEL_EDGE, image, 256, 64);

    image = tp.LoadTexture("res/tex/statravelbracket.raw", 16, 2);
    tp.CreateTexture(STA_TRAVEL_BRACKET, image, 16, 2);

    image = tp.LoadTexture("res/tex/statravel2.raw", 256, 256);
    tp.CreateTexture(STA_TRAVEL_2, image, 256, 256);

    image = tp.LoadTexture("res/tex/statravelbottom.raw", 2, 64);
    tp.CreateTexture(STA_TRAVEL_BOTTOM, image, 2, 64);

    image = tp.LoadTexture("res/tex/stepbricks.raw", 128, 128);
    tp.CreateTexture(WALL_BRICK_STEPS, image, 128, 128);

    image = tp.LoadTexture("res/tex/stepbrickscover.raw", 64, 128);
    tp.CreateTexture(WALL_BRICK_STEPS_COVER, image, 64, 128);

    image = tp.LoadTexture("res/tex/stepbricksedge.raw", 64, 32);
    tp.CreateTexture(WALL_BRICK_STEPS_EDGE, image, 64, 32);

    image = tp.LoadTexture("res/tex/stepbricksedge2.raw", 64, 64);
    tp.CreateTexture(WALL_BRICK_STEPS_EDGE_2, image, 64, 64);

    image = tp.LoadTexture("res/tex/stepbrickstop.raw", 32, 128);
    tp.CreateTexture(WALL_BRICK_STEPS_TOP, image, 32, 128);

    image = tp.LoadTexture("res/tex/stepslibrary.raw", 128, 1024);
    tp.CreateTexture(STEPS_LIBRARY, image, 128, 1024);

    image = tp.LoadTexture("res/tex/stepslibrarytop.raw", 256, 1024);
    tp.CreateTexture(STEPS_LIBRARY_TOP, image, 256, 1024);

    image = tp.LoadTexture("res/tex/steppaving1.raw", 1024, 512);
    tp.CreateTexture(STEP_PAVING_1, image, 1024, 512);

    image = tp.LoadTexture("res/tex/steppavingedge.raw", 64, 64);
    tp.CreateTexture(STEP_EDGE, image, 64, 64);

    image = tp.LoadTexture("res/tex/sweetmachine.raw", 256, 256);
    tp.CreateTexture(SWEET_MACHINE, image, 256, 256);

    image = tp.LoadTexture("res/tex/telephoneback.raw", 512, 512);
    tp.CreateTexture(TELEPHONE_BACK, image, 512, 512);

    image = tp.LoadTexture("res/tex/ticketcounteredge2.raw", 64, 64);
    tp.CreateTexture(TICKET_COUNTER_EDGE_2, image, 64, 64);

    image = tp.LoadTexture("res/tex/ticketcounteredge3.raw", 64, 64);
    tp.CreateTexture(TICKET_COUNTER_EDGE_3, image, 64, 64);

    image = tp.LoadTexture("res/tex/ticketcountertop.raw", 128, 256);
    tp.CreateTexture(TICKET_COUNTER_TOP, image, 128, 256);

    image = tp.LoadTexture("res/tex/ticketledgeedge.raw", 2, 32);
    tp.CreateTexture(TICKET_LEDGE_EDGE, image, 2, 32);

    image = tp.LoadTexture("res/tex/ticketledge.raw", 2, 128);
    tp.CreateTexture(TICKET_LEDGE, image, 2, 128);

    image = tp.LoadTexture("res/tex/ticketledgeedge2.raw", 32, 2);
    tp.CreateTexture(TICKET_LEDGE_EDGE_2, image, 32, 2);

    image = tp.LoadTexture("res/tex/ticketcounteredge.raw", 128, 32);
    tp.CreateTexture(TICKET_COUNTER_EDGE, image, 128, 32);

    image = tp.LoadTexture("res/tex/toiletdoortop.raw", 32, 256);
    tp.CreateTexture(TOILET_DOOR_TOP, image, 32, 256);

    image = tp.LoadTexture("res/tex/toiletmen.raw", 128, 128);
    tp.CreateTexture(TOILET_MEN, image, 128, 128);

    image = tp.LoadTexture("res/tex/toiletwomen.raw", 128, 128);
    tp.CreateTexture(TOILET_WOMEN, image, 128, 128);

    image = tp.LoadTexture("res/tex/wallgap1.raw", 8, 128);
    tp.CreateTexture(WALL_GAP_1, image, 8, 128);

    image = tp.LoadTexture("res/tex/windowledge1.raw", 32, 1024);
    tp.CreateTexture(WINDOWLEDGE_CHANC_FRONT, image, 32, 1024);

    image = tp.LoadTexture("res/tex/windowledge2.raw", 128, 1024);
    tp.CreateTexture(WINDOWLEDGE_CHANC_TOP, image, 128, 1024);

    image = tp.LoadTexture("res/tex/windowledgeend.raw", 32, 64);
    tp.CreateTexture(WINDOW_LEDGE_END_1, image, 32, 64);

    image = tp.LoadTexture("res/tex/windowledgeend2.raw", 64, 64);
    tp.CreateTexture(WINDOW_LEDGE_END_2, image, 64, 64);

    image = tp.LoadTexture("res/tex/windowledgelibfa.raw", 1024, 32);
    tp.CreateTexture(WINDOWLEDGE_LIB_A, image, 1024, 32);

    image = tp.LoadTexture("res/tex/windowledgelibfb.raw", 1024, 32);
    tp.CreateTexture(WINDOWLEDGE_LIB_B, image, 1024, 32);

    image = tp.LoadTexture("res/tex/windowledgelibta.raw", 1024, 128);
    tp.CreateTexture(WINDOWLEDGE_LIB_TOP_A, image, 1024, 128);

    image = tp.LoadTexture("res/tex/windowledgelibtb.raw", 1024, 128);
    tp.CreateTexture(WINDOWLEDGE_LIB_TOP_B, image, 1024, 128);

    image = tp.LoadTexture("res/tex/windowledgeus1.raw", 32, 1024);
    tp.CreateTexture(WINDOWLEDGE_PS_FRONT, image, 32, 1024);

    image = tp.LoadTexture("res/tex/windowledgeus2.raw", 128, 1024);
    tp.CreateTexture(WINDOWLEDGE_PS_TOP, image, 128, 1024);

    image = tp.LoadTexture("res/tex/windowledgeus3.raw", 128, 1024);
    tp.CreateTexture(WINDOWLEDGE_PS_BOTT, image, 128, 1024);

    image = tp.LoadTexture("res/tex/windowpost1.raw", 1024, 128);
    tp.CreateTexture(WINDOWPOST_CHANC_FRONT, image, 1024, 128);

    image = tp.LoadTexture("res/tex/windowpostsmall.raw", 512, 128);
    tp.CreateTexture(WINDOWPOST_PHYSSCI_FRONT, image, 512, 128);

    image = tp.LoadTexture("res/tex/windowpostsmallside2.raw", 64, 512);
    tp.CreateTexture(WINDOWPOST_PHYSSCI_RIGHT, image, 64, 512);

    image = tp.LoadTexture("res/tex/windowpostsmallside.raw", 64, 512);
    tp.CreateTexture(WINDOWPOST_PHYSSCI_LEFT, image, 64, 512);

    image = tp.LoadTexture("res/tex/windowpostlib.raw", 128, 512);
    tp.CreateTexture(WINDOWPOST_LIB_FRONT, image, 128, 512);

    image = tp.LoadTexture("res/tex/windowpostlibside1.raw", 512, 64);
    tp.CreateTexture(WINDOWPOST_LIB_LEFT, image, 512, 64);

    image = tp.LoadTexture("res/tex/windowpostlibside2.raw", 512, 64);
    tp.CreateTexture(WINDOWPOST_LIB_RIGHT, image, 512, 64);

    image = tp.LoadTexture("res/tex/windowposthalf1.raw", 64, 1024);
    tp.CreateTexture(WINDOWPOST_CHANC_RIGHT, image, 64, 1024);

    image = tp.LoadTexture("res/tex/windowposthalf2.raw", 64, 1024);
    tp.CreateTexture(WINDOWPOST_CHANC_LEFT, image, 64, 1024);

    // Larger Textures

    image = tp.LoadTexture("res/tex/windows/stepwindow.raw", 128, 256);
    tp.CreateTexture(STEP_WINDOW, image, 128, 256);

    image = tp.LoadTexture("res/tex/windows/chancdoor1.raw", 256, 256);
    tp.CreateTexture(CHANC_DOOR_1, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/chancdoor2.raw", 256, 256);
    tp.CreateTexture(CHANC_DOOR_2, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/entrance.raw", 512, 256);
    tp.CreateTexture(ENTRANCE, image, 512, 256);

    image = tp.LoadTexture("res/tex/windows/entrance2.raw", 512, 512);
    tp.CreateTexture(ENTRANCE_2, image, 512, 512);

    image = tp.LoadTexture("res/tex/windows/exiteast.raw", 512, 512);
    tp.CreateTexture(EXIT_EAST, image, 512, 512);

    image = tp.LoadTexture("res/tex/windows/exitwest.raw", 256, 512);
    tp.CreateTexture(EXIT_WEST, image, 256, 512);

    image = tp.LoadTexture("res/tex/windows/window1.raw", 256, 256);
    tp.CreateTexture(WINDOW_1, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window1b.raw", 256, 256);
    tp.CreateTexture(WINDOW_1B, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window2.raw", 256, 256);
    tp.CreateTexture(WINDOW_2, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window2b.raw", 256, 256);
    tp.CreateTexture(WINDOW_2B, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window2c.raw", 256, 256);
    tp.CreateTexture(WINDOW_2C, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window2d.raw", 256, 256);
    tp.CreateTexture(WINDOW_2D, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window2e.raw", 256, 256);
    tp.CreateTexture(WINDOW_2E, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window2us.raw", 256, 256);
    tp.CreateTexture(WINDOW_2US, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window2usb.raw", 256, 256);
    tp.CreateTexture(WINDOW_2USB, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window3.raw", 256, 256);
    tp.CreateTexture(WINDOW_3, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window3b.raw", 256, 256);
    tp.CreateTexture(WINDOW_3B, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window4.raw", 128, 256);
    tp.CreateTexture(WINDOW_4, image, 128, 256);

    image = tp.LoadTexture("res/tex/windows/window5.raw", 128, 256);
    tp.CreateTexture(WINDOW_5, image, 128, 256);

    image = tp.LoadTexture("res/tex/windows/window6.raw", 256, 256);
    tp.CreateTexture(WINDOW_6, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window7.raw", 256, 256);
    tp.CreateTexture(WINDOW_7, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window8.raw", 256, 256);
    tp.CreateTexture(WINDOW_8, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window9.raw", 256, 256);
    tp.CreateTexture(WINDOW_9, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window10.raw", 256, 256);
    tp.CreateTexture(WINDOW_10, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window11.raw", 256, 256);
    tp.CreateTexture(WINDOW_11, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window12.raw", 256, 256);
    tp.CreateTexture(WINDOW_12, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window13.raw", 256, 256);
    tp.CreateTexture(WINDOW_13, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window14.raw", 256, 128);
    tp.CreateTexture(WINDOW_14, image, 256, 128);

    image = tp.LoadTexture("res/tex/windows/window14b.raw", 256, 128);
    tp.CreateTexture(WINDOW_14B, image, 256, 128);

    image = tp.LoadTexture("res/tex/windows/window15.raw", 256, 256);
    tp.CreateTexture(WINDOW_15, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/window16.raw", 128, 256);
    tp.CreateTexture(WINDOW_16, image, 128, 256);

    image = tp.LoadTexture("res/tex/windows/window17.raw", 128, 256);
    tp.CreateTexture(WINDOW_17, image, 128, 256);

    image = tp.LoadTexture("res/tex/windows/windowlib1.raw", 256, 128);
    tp.CreateTexture(WINDOW_LIB_1, image, 256, 128);

    image = tp.LoadTexture("res/tex/windows/windowlib1a.raw", 256, 128);
    tp.CreateTexture(WINDOW_LIB_1A, image, 256, 128);

    image = tp.LoadTexture("res/tex/windows/windowlib1b.raw", 256, 128);
    tp.CreateTexture(WINDOW_LIB_1B, image, 256, 128);

    image = tp.LoadTexture("res/tex/windows/windowlib1c.raw", 256, 128);
    tp.CreateTexture(WINDOW_LIB_1C, image, 256, 128);

    image = tp.LoadTexture("res/tex/windows/windowlibusa.raw", 256, 128);
    tp.CreateTexture(WINDOW_LIB_US_A, image, 256, 128);

    image = tp.LoadTexture("res/tex/windows/windowlibusb.raw", 256, 128);
    tp.CreateTexture(WINDOW_LIB_US_B, image, 256, 128);

    image = tp.LoadTexture("res/tex/windows/windowlibdoor1.raw", 256, 256);
    tp.CreateTexture(WINDOW_LIB_DOOR_1, image, 256, 256);

    image = tp.LoadTexture("res/tex/windows/windowlibdoor2.raw", 512, 256);
    tp.CreateTexture(WINDOW_LIB_DOOR_2, image, 512, 256);

    image = tp.LoadTexture("res/tex/windows/windowliblong.raw", 256, 128);
    tp.CreateTexture(WINDOW_LIB_LONG, image, 256, 128);

    image = tp.LoadTexture("res/tex/map.raw", 256, 256);
    tp.CreateTexture(217, image, 256, 256);
    image = tp.LoadTexture("res/tex/welcome.raw", 512, 512);
    tp.CreateTexture(218, image, 512, 512);
    image = tp.LoadTexture("res/tex/thanks.raw", 512, 512);
    tp.CreateTexture(219, image, 512, 512);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//--------------------------------------------------------------------------------------
//  Called from the main display function to draw the backdrop (all images)
//--------------------------------------------------------------------------------------
void DrawBackdrop() {
    DisplayAboveWindowBlock();
    DisplayBench();
    DisplayBricks();
    DisplayChancPosts();
    DisplayCylinders();
    DisplayDoorPaving();
    DisplayDoorPosts();
    DisplayEntranceSteps();
    DisplayExtras();
    DisplayGrass();
    DisplayLargerTextures();
    DisplayLibraryPosts();
    DisplayMainPosts();
    DisplayPavement();
    DisplayPhysSciPosts();
    DisplayPurplePosts();
    DisplayRedPosts();
    DisplayRoof();
    DisplayStepBricks();
    if (lightsOn)
        DisplayLights();
}

//--------------------------------------------------------------------------------------
// Display the chancellery windoe and door posts
//--------------------------------------------------------------------------------------
void DisplayChancPosts() {
    // Windowposts Chanc (downstairs)
    step = 0.0f;
    for (int i = 0; i < 14; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        if ((i != 1) && (i != 2) && (i != 10) && (i != 11)) {
            glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_FRONT));
            glCallList(11);
        }
        if ((i != 1) && (i != 10)) {
            glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_RIGHT));
            glCallList(12);
        }
        if ((i != 2) && (i != 11)) {
            glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_LEFT));
            glCallList(13);
        }

        glPopMatrix();
        step += 960.0f;
    }

    //  Windowledges Chanc (downstairs)
    step = 0.0f;
    for (int i = 0; i < 11; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_FRONT));
        glCallList(14);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_TOP));
        glCallList(15);
        glPopMatrix();
        if ((i == 0) || (i == 8))
            step += 960.0f;
        step += 960.0f;
    }

    // Windowposts & Ledges Chanc (upstairs)
    glPushMatrix();
    step = 0.0f;
    glTranslatef(0.0f, 1023.0f, 0.0f);
    for (int i = 0; i < 14; i++) {
        glTranslatef(0.0f, 0.0f, step);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_FRONT));
        glCallList(11);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_RIGHT));
        glCallList(12);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_CHANC_LEFT));
        glCallList(13);
        if (i != 13) {
            glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_FRONT));
            glCallList(14);

            glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_CHANC_TOP));
            glCallList(15);
        }
        step = +960.0f;
    }
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LEDGE_END_1));
    glCallList(235);
    glPushMatrix();
    glTranslatef(0.0f, 320.0f, 7447.0f);
    glCallList(235);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 1024.0f, 0.0f);
    glCallList(235);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 320.0f, 5527.0f);
    glCallList(235);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 320.0f, 6551.0f);
    glCallList(235);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 320.0f, 8471.0f);
    glCallList(235);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 1152.0f, 19031.0f);
    glCallList(235);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LEDGE_END_2));
    glCallList(236);
    glCallList(237);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -960.0f);
    glCallList(237);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -8640.0f);
    glCallList(237);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -9600.0f);
    glCallList(237);
    glPopMatrix();

    // glPushMatrix();
    // glTranslatef(0.0f, 320.0f, -9600.0f);
    // glCallList(237);
    //	glPopMatrix();

    // angled corner of window ledges
    glPushMatrix();
    glTranslatef(0.0f, 1024.0f, 0.0f);
    glCallList(236);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 320.0f, 7383.0f);
    glCallList(236);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 320.0f, 5463.0f);
    glCallList(236);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 320.0f, 6551.0f);
    glCallList(236);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 320.0f, 8471.0f);
    glCallList(236);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 1152.0f, 19031.0f);
    glCallList(236);
    glPopMatrix();
}

void DrawChancPosts() {
    // Front of Window Post Chanc
    tp.CreateDisplayList(YZ, 11, 1024.0f, 128.0f, 33848.0f, 10237.0f, 9505.0f,
                         0.586f, 0.7344f);
    // Right side of Window Post Chanc
    tp.CreateDisplayList(XY, 12, 64.0f, 1024.0f, 33848.0f, 10237.0f, 9599.0f,
                         0.7344f, 0.585f);
    // Left side of Window Post Chanc
    tp.CreateDisplayList(XY, 13, 64.0f, 1024.0f, 33848.0f, 10237.0f, 9505.0f,
                         0.7344f, 0.585f);

    // Window ledges of Chanc
    tp.CreateDisplayList(YZ, 14, 32.0f, 1024.0f, 33808.0f, 10192.0f, 9552.0f, 1.0f,
                         0.9375f); // front ledge
    glNewList(15, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(33808.0f, 10224.0f, 9552.0f);
    glTexCoord2f(0.0f, 0.9375f);
    glVertex3f(33808.0f, 10224.0f, 9552.0f + (1024.0f * 0.9375f));
    glTexCoord2f(1.0f, 0.9375f);
    glVertex3f(33928.0f, 10268.0f, 9552.0f + (1024.0f * 0.9375f));
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(33928.0f, 10268.0f, 9552.0f);
    glEnd();
    glEndList();
    tp.CreateDisplayList(YZ, 235, 32.0f, 64.0f, 33808.0f, 10192.0f, 22032.0f, 1.0f,
                         1.0f); // front ledge
    tp.CreateDisplayList(XY, 236, 64.0f, 64.0f, 33808.0f, 10192.0f, 22096.0f, 1.35f,
                         0.5f); // front ledge

    // Window Edges
    glNewList(237, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(33808.0f, 10225.0f, 20112.0f);
    glTexCoord2f(0.0f, 0.5f);
    glVertex3f(33808.0f, 10192.0f, 20112.0f);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(33872.0f, 10192.0f, 20112.0f);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(33872.0f, 10247.0f, 20112.0f);
    glEnd();
    glEndList();
}

//--------------------------------------------------------------------------------------
// Display Door Posts
//--------------------------------------------------------------------------------------

void DisplayDoorPosts() {
    // Door Posts Chanc
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_SECURITY));
    glCallList(199);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_CHANC));
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 8640.0f);
    glCallList(25);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_CHANC));
    glCallList(26);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 8640.0f);
    glCallList(26);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_SIDEPOST_CHANC));
    glCallList(27);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 866.0f);
    glCallList(27);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 8640.0f);
    glCallList(27);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 9506.0f);
    glCallList(27);
    glPopMatrix();
}

void DrawDoorPosts() {
    // DOORPOSTS_CHANC
    tp.CreateDisplayList(YZ_FLIP, 25, 1024.0f, 128.0f, 33848.0f, 10000.0f,
                         10465.0f, 0.83f, 0.7344f); // post
    tp.CreateDisplayList(YZ, 26, 1024.0f, 128.0f, 33848.0f, 10000.0f, 11425.0f,
                         0.83f, 0.7344f);
    tp.CreateDisplayList(XY, 27, 64.0f, 1024.0f, 33848.0f, 10000.0f, 10559.0f, 1.0f,
                         1.0f); // sidepost
    tp.CreateDisplayList(YZ_FLIP, 199, 1024.0f, 128.0f, 33848.0f, 10000.0f,
                         10465.0f, 0.83f, 0.7344f); // post
}

//--------------------------------------------------------------------------------------
// Display blocks above Windows and Posts
//--------------------------------------------------------------------------------------
void DisplayAboveWindowBlock() {
    // Blocks Above Windows Chanc & Phys Sci
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK));
    glCallList(20);
    glCallList(223);
    glCallList(229);
    // Blocks containing text
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_TEXT));
    glCallList(224);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_TEXT_2));
    glCallList(225);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_TEXT_3));
    glCallList(230);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_PHYS_SCI_TEXT));
    glCallList(226);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 9728.0f);
    glCallList(226);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_2));
    glCallList(44);
    glCallList(46);
    glCallList(96);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_CHANC));
    glCallList(22);
    glPushMatrix();
    glTranslatef(0.0f, 1024.0f, 0.0f);
    glCallList(22);
    glPopMatrix();
    glCallList(24);
    glPushMatrix();
    glTranslatef(0.0f, 1024.0f, 0.0f);
    glCallList(24);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_3));
    glCallList(227);
    glCallList(228);
    glCallList(21);
    glCallList(23);
    glCallList(95);
    glPushMatrix();
    glTranslatef(99.84f, 0.0f, 0.0f);
    glCallList(95);
    glPopMatrix();
    glCallList(231);
    glCallList(43);
    glCallList(45);
    glCallList(53); // aboves posts
    glPushMatrix();
    glTranslatef(128.0f, 0.0f, 0.0f);
    glCallList(53);
    glPopMatrix();
    glCallList(68);
    glCallList(71); // above post between chanc and phys sci

    glCallList(213);
    glPushMatrix();
    glTranslatef(0.0f, 1024.0f, 0.0f);
    glCallList(213);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_EDGE_3B));
    glCallList(49);
    glPushMatrix();
    glTranslatef(0.0f, 1024.0f, 0.0f);
    glCallList(49);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 1024.0f, 15783.0f);
    glCallList(49);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-2068.0f, 310.0f, -17244.0f);
    glCallList(49);
    glPopMatrix();
    glCallList(425);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_XY_3));
    glCallList(50);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 807.0f);
    glCallList(50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 9567.0f);
    glCallList(50);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 11103.0f);
    glCallList(50);
    glPopMatrix();
    for (GLuint i = 64; i < 67; i++)
        glCallList(i);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 128.0f);
    glCallList(66);
    glPopMatrix();
    glCallList(208);
    glCallList(233);
    glCallList(234);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_UNDER_POSTS));
    glCallList(54);
    glCallList(67);
    glCallList(72);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BELOW_ROOF_FILL));
    glCallList(39);

    // -------------------------------- Above under Mainpost by Library -----------------------
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_UNDER_POSTS_2));
    glCallList(69);
    glCallList(232);

    // -------------------------------- Above Library ------------------------------------
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_LIB));
    for (GLuint i = 55; i < 57; i++)
        glCallList(i);
    glCallList(238);
    glCallList(415);
    glCallList(417);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_UNDER_LIB));
    for (GLuint i = 70; i < 71; i++)
        glCallList(i);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_EDGE_3B_LIB));
    glCallList(209);
    step = 17536.0f;
    for (GLuint i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);
        glCallList(209);
        glPopMatrix();
        step += 128.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_EDGE_4B_LIB));
    glCallList(210);
    step = 17536.0f;
    for (GLuint i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);
        glCallList(210);
        glPopMatrix();
        step += 128.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_UNDER_4B));
    for (GLuint i = 211; i < 213; i++)
        glCallList(i);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_LIB_TEXT));
    glCallList(239);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_LIB_TEXT_2));
    glCallList(416);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_TICKETS_TEXT));
    glCallList(418);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_CHANC_EDGE));
    glCallList(424);
}

void DrawAboveWindowBlock() {
    tp.CreateDisplayList(YZ, 20, 128.0f, 256.0f, 33808.0f, 10832.0f, 9552.0f, 1.0f,
                         4.0f); // chanc above bottom window
    tp.CreateDisplayList(YZ, 223, 128.0f, 256.0f, 33808.0f, 10832.0f, 11600.0f, 1.0f,
                         30.0f); // chanc above bottom window
    tp.CreateDisplayList(YZ, 229, 128.0f, 256.0f, 33808.0f, 10832.0f, 20304.0f, 1.0f,
                         3.0f); // chanc above bottom window
    tp.CreateDisplayList(YZ, 230, 128.0f, 1024.0f, 33808.0f, 10832.0f, 19280.0f,
                         1.0f,
                         1.0f); // chanc above bottom window
    tp.CreateDisplayList(YZ, 224, 128.0f, 1024.0f, 33808.0f, 10832.0f, 10576.0f,
                         1.0f,
                         1.0f); // chanc above bottom window
    tp.CreateDisplayList(YZ, 225, 128.0f, 1024.0f, 33808.0f, 10832.0f, 21072.0f,
                         1.0f,
                         1.0f); // chanc above bottom window
    tp.CreateDisplayList(XY, 424, 128.0f, 128.0f, 33808.0f, 10832.0f, 22096.0f,
                         0.68f,
                         1.0f); // chanc end edge downstairs
    tp.CreateDisplayList(XY, 425, 128.0f, 256.0f, 33808.0f, 11856.0f, 22096.0f,
                         0.68f,
                         0.5625f); // 3 bricks high to edge

    tp.CreateDisplayList(YZ, 21, 256.0f, 256.0f, 33808.0f, 11856.0f, 9552.0f, 0.56f,
                         49.0f); // chanc above top window chanc
    tp.CreateDisplayList(XZ, 22, 128.0f, 256.0f, 33808.0f, 10832.0f, 9552.0f, 0.70f,
                         49.0f); // chanc above under bottom window chanc

    tp.CreateDisplayList(YZ, 23, 256.0f, 256.0f, 33808.0f, 10832.0f, 25344.0f, 0.75f,
                         5.0f); // phys sci above bottom window
    tp.CreateDisplayList(YZ, 231, 256.0f, 256.0f, 33808.0f, 11856.0f, 25344.0f,
                         0.75f,
                         61.652f); // phys sci above bottom window

    tp.CreateDisplayList(YZ, 226, 256.0f, 1024.0f, 33808.0f, 10832.0f, 26624.0f,
                         0.75f, 1.0f); // phys sci text
    tp.CreateDisplayList(YZ, 227, 256.0f, 256.0f, 33808.0f, 10832.0f, 27648.0f,
                         0.75f,
                         34.0f); // phys sci above bottom window
    tp.CreateDisplayList(YZ, 228, 256.0f, 256.0f, 33808.0f, 10832.0f, 37376.0f,
                         0.75f,
                         14.652f); // phys sci above bottom window
    tp.CreateDisplayList(XZ, 24, 128.0f, 256.0f, 33808.0f, 10832.0f, 25344.0f, 0.78f,
                         61.652f); // phys sci above under bottom window

    tp.CreateDisplayList(YZ, 95, 256.0f, 256.0f, 33835.0f, 11856.0f, 41127.0f, 1.0f,
                         7.6f); // phys sci above top window
    tp.CreateDisplayList(XZ, 96, 128.0f, 256.0f, 33835.0f, 11856.0f, 41127.0f, 0.78f,
                         7.6f); // phys sci above under bottom

    tp.CreateDisplayList(YZ, 43, 256.0f, 256.0f, 34256.0f, 10832.0f, 26752.0f, 0.75f,
                         3.25f); // phys sci above 1st door
    tp.CreateDisplayList(XZ, 44, 128.0f, 256.0f, 34256.0f, 10832.0f, 26752.0f, 0.70f,
                         2.25f); // phys sci above under 1st door
    tp.CreateDisplayList(YZ, 45, 256.0f, 256.0f, 34256.0f, 10832.0f, 36319.0f, 0.75f,
                         6.125f); // phys sci above 2nd door
    tp.CreateDisplayList(XZ, 46, 128.0f, 256.0f, 34256.0f, 10832.0f, 36319.0f, 0.70f,
                         6.125f); // phys sci above under 2nd door

    tp.CreateDisplayList(YZ, 53, 256.0f, 256.0f, 31740.0f, 11142.0f, 8100.0f, 0.75f,
                         128.955f); // above posts chanc and canteen sides
    tp.CreateDisplayList(XZ, 54, 128.0f, 256.0f, 31740.0f, 11142.0f, 8100.0f, 1.0f,
                         128.955f); // above under main posts
    tp.CreateDisplayList(XZ, 67, 128.0f, 256.0f, 35920.0f, 10832.0f, 41127.0f, 1.0f,
                         7.6f); // above under steps at end of phys sci
    tp.CreateDisplayList(YZ, 68, 256.0f, 256.0f, 35920.0f, 10832.0f, 41127.0f, 0.75f,
                         7.6f); // above steps at end of phys sci
    tp.CreateDisplayList(YZ, 39, 128.0f, 256.0f, 35990.0f, 11002.0f, 41127.0f, 0.75f,
                         7.6f); // above steps at end of phys sci (darker back bit)
    tp.CreateDisplayList(XZ, 69, 256.0f, 128.0f, 4580.0f, 11142.0f, 40985.0f,
                         106.094f,
                         1.0f); // ABOVE_UNDER_POSTS_2 main posts by library
    tp.CreateDisplayList(YZ, 71, 256.0f, 256.0f, 35748.0f, 11142.0f, 22096.0f, 0.75f,
                         12.69f); // above post between chanc and phys sci
    tp.CreateDisplayList(XZ, 72, 128.0f, 256.0f, 35748.0f, 11142.0f, 22096.0f, 1.0f,
                         12.69f); // above under post between chanc and phys sci

    glNewList(232, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(31768.0f + 45.0f, 11162.0f, 41011.2f - 45.0f);
    glTexCoord2f(10.54f, 0.0f);
    glVertex3f(33848.0f + 45.0f, 11920.0f, 43095.2f - 45.0f);
    glTexCoord2f(10.54f, 1.0f);
    glVertex3f(33848.0f - 45.0f, 11920.0f, 43095.2f + 45.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(31768.0f - 45.0f, 11162.0f, 41011.2f + 45.0f);
    glEnd();
    glEndList();

    glNewList(233, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(31768.0f - 45.0f, 11162.0f, 41011.2f + 45.0f);
    glTexCoord2f(10.54f, 0.0f);
    glVertex3f(33848.0f - 45.0f, 11920.0f, 43095.2f + 45.0f);
    glTexCoord2f(10.54f, 0.75f);
    glVertex3f(33848.0f - 45.0f, 11920.0f + 192.0f, 43095.2f + 45.0f);
    glTexCoord2f(0.0f, 0.75f);
    glVertex3f(31768.0f - 45.0f, 11162.0f + 192.0f, 41011.20f + 45.0f);
    glEnd();
    glEndList();

    glNewList(234, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(31768.0f + 45.0f, 11162.0f, 41011.2f - 45.0f);
    glTexCoord2f(10.54f, 0.0f);
    glVertex3f(33848.0f + 45.0f, 11920.0f, 43095.2f - 45.0f);
    glTexCoord2f(10.54f, 0.75f);
    glVertex3f(33848.0f + 45.0f, 11920.0f + 192.0f, 43095.2f - 45.0f);
    glTexCoord2f(0.0f, 0.75f);
    glVertex3f(31768.0f + 45, 11162.0f + 192.0f, 41011.2f - 45.0f);
    glEnd();
    glEndList();

    // ABOVE_WINDOW_EDGE_3B
    tp.CreateDisplayList(XY, 49, 128.0f, 256.0f, 33808.0f, 10832.0f, 25344.0f, 1.0f,
                         0.75f); // 3 bricks high

    // ABOVE_WINDOW_BLOCK_XY_3
    tp.CreateDisplayList(XY, 50, 256.0f, 256.0f, 33888.0f, 10832.0f, 26752.0f,
                         1.5f, 1.0f);
    tp.CreateDisplayList(XY, 64, 256.0f, 256.0f, 33808.0f, 10832.0f, 41127.0f, 8.5f,
                         0.75f); // above end phys sci
    tp.CreateDisplayList(XY, 65, 256.0f, 256.0f, 6600.0f, 11856.0f, 43056.0f, 68.5f,
                         0.75f); // top of library
    tp.CreateDisplayList(XY, 208, 256.0f, 256.0f, 24264.0f, 11856.0f, 43056.0f,
                         38.5f,
                         0.75f); // top of library
    tp.CreateDisplayList(XY, 66, 256.0f, 256.0f, 4548.0f, 11142.0f, 40985.0f,
                         106.72f,
                         0.75f); // above library main posts

    // ABOVE_LIB
    tp.CreateDisplayList(XY, 239, 1024.0f, 256.0f, 31504.96f, 10768.0f,
                         43056.0f, 1.0f, 1.0f); // (above KBLT)
    tp.CreateDisplayList(XY, 238, 256.0f, 256.0f, 32528.96f, 10768.0f, 43056.0f,
                         13.75f, 1.0f); // (above KBLT)
    tp.CreateDisplayList(XY, 55, 256.0f, 256.0f, 24264.0f, 10768.0f, 43056.0f,
                         28.285f, 1.0f); // (above KBLT)
    tp.CreateDisplayList(XY, 416, 1024.0f, 256.0f, 9416.0f, 10768.0f, 43056.0f, 1.0f,
                         1.0f); // (above library text)
    tp.CreateDisplayList(XY, 415, 256.0f, 256.0f, 10440.0f, 10768.0f, 43056.0f,
                         49.0f,
                         1.0f); // (above library)
    tp.CreateDisplayList(XY, 417, 256.0f, 256.0f, 23240.0f, 10768.0f, 43056.0f, 3.5f,
                         1.0f); // (above library)
    tp.CreateDisplayList(XY, 418, 256.0f, 256.0f, 22984.0f, 10768.0f, 43056.0f, 1.0f,
                         1.0f); // (above library ticket text)
    tp.CreateDisplayList(XY, 56, 256.0f, 256.0f, 6600.0f, 10768.0f, 43056.0f, 11.0f,
                         1.0f); // (above library)
    tp.CreateDisplayList(XZ, 70, 256.0f, 128.0f, 8189.0f, 11856.0f, 43056.0f, 62.3f,
                         0.75f); // above under upstairs
    tp.CreateDisplayList(YZ, 209, 256.0f, 64.0f, 6600.0f, 11856.0f, 43056.0f,
                         1.2f, 1.0f);
    tp.CreateDisplayList(YZ, 210, 256.0f, 64.0f, 6600.0f, 10768.0f, 43056.0f,
                         1.0f, 1.0f);
    tp.CreateDisplayList(XZ, 211, 256.0f, 128.0f, 8189.0f, 10768.0f, 43056.0f, 62.3f,
                         0.75f); // above under downstairs
    tp.CreateDisplayList(XZ, 212, 256.0f, 128.0f, 32720.0f, 10768.0f, 43056.0f, 3.5f,
                         0.75f); // above under gcl1

    // ABOVE CANTEEN
    tp.CreateDisplayList(YZ, 213, 256.0f, 256.0f, 2608.0f, 10896.0f, 10000.0f,
                         0.78f, 139.25f);
}

//--------------------------------------------------------------------------------------
// Display Purple Posts by Guild Shop
//--------------------------------------------------------------------------------------
void DisplayPurplePosts() {
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PURPLE_POST));
    glCallList(29);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 4800.0f);
    glCallList(29);
    glPopMatrix();
    glCallList(30);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 960.0f);
    glCallList(30);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 2880.0f);
    glCallList(30);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PURPLE_POSTSIDE));
    glCallList(31);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -112.0f);
    glCallList(31);
    glPopMatrix();

    step = 865.0f;
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(31);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step + 78.0f);
        glCallList(31);
        glPopMatrix();
        step += 960.0f;
        if (i == 1)
            step += 960.0f;
    }
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 4688.0f);
    glCallList(31);
    glPopMatrix();
    glCallList(32);
}

void DrawPurplePosts() {
    tp.CreateDisplayList(YZ, 29, 64.0f, 128.0f, 33802.0f, 10000.0f, 31407.0f, 13.0f,
                         0.875f); // front
    tp.CreateDisplayList(YZ, 30, 64.0f, 128.0f, 33802.0f, 10000.0f, 32384.0f, 13.0f,
                         0.61f); // front
    tp.CreateDisplayList(XY, 31, 128.0f, 64.0f, 33802.0f, 10000.0f, 31519.0f, 0.75f,
                         13.0f); // side
    tp.CreateDisplayList(XY, 32, 128.0f, 64.0f, 33802.0f, 10000.0f, 36319.0f, 0.58f,
                         13.0f); // side
}

//--------------------------------------------------------------------------------------
// Display Red Posts by Sta Travel Shop
//--------------------------------------------------------------------------------------

void DisplayRedPosts() {
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(RED_POST));
    glCallList(33);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1399.0f);
    glCallList(33);
    glPopMatrix();
    glCallList(34);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(RED_POSTSIDE));
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 240.0f);
    glCallList(35);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 256.0f);
    glCallList(35);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1639.0f);
    glCallList(35);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1095.0f);
    glCallList(35);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1191.0f);
    glCallList(35);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1655.0f);
    glCallList(35);
    glPopMatrix();
}

void DrawRedPosts() {
    tp.CreateDisplayList(YZ, 33, 64.0f, 128.0f, 33802.0f, 10000.0f, 39200.0f, 13.0f,
                         0.125f); // front
    tp.CreateDisplayList(YZ, 34, 64.0f, 128.0f, 33802.0f, 10000.0f, 40055.0f, 13.0f,
                         0.75f); // front
    tp.CreateDisplayList(XY, 35, 64.0f, 64.0f, 33802.0f, 10000.0f, 38960.0f, 1.0f,
                         13.0f); // side
}

//--------------------------------------------------------------------------------------
// Display Main Posts
//--------------------------------------------------------------------------------------
void DisplayMainPosts() {
    step       = 0.0f;
    stepLength = 0.0f;
    step2      = 0.0f;
    for (int j = 0; j < 2; j++) {
        glPushMatrix();
        glTranslatef(stepLength, 0.0f, step2);
        for (int i = 0; i < 17; i++) {
            glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, step);
            glCallList(18);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, step + 128.0f);
            glCallList(18);
            glPopMatrix();
            if ((i == 7) && (j == 0)) // between chanc and phys sci
            {
                glPushMatrix();
                glTranslatef(4008.0f, 0.0f, step);
                glCallList(18);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(4008.0f, 0.0f, step + 128.0f);
                glCallList(18);
                glPopMatrix();
            }

            glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, step);
            glCallList(19);
            glPopMatrix();
            glPushMatrix();
            glTranslatef(128.0f, 0.0f, step);
            glCallList(19);
            glPopMatrix();
            if ((i == 7) && (j == 0)) // between chanc and phys sci
            {
                glPushMatrix();
                glTranslatef(4008.0f, 0.0f, step);
                glCallList(19);
                glPopMatrix();
            }
            step += 1930.0f;
        }
        stepLength -= 27192.0f;
        step2 -= 32810.0f;
        glPopMatrix();
    }

    // library front
    step = -1940.0f;
    for (int i = 0; i < 13; i++) {
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
        glPushMatrix();
        glTranslatef(step, 0.0f, 30880.0f);
        glCallList(18);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(step, 0.0f, 31008.0f);
        glCallList(18);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
        glPushMatrix();
        glTranslatef(step, 0.0f, 30880.0f);
        glCallList(19);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(step + 128.0f, 0.0f, 30880.0f);
        glCallList(19);
        glPopMatrix();
        step -= 1940.0f;
    }

    // first on chanc steps
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST));
    glCallList(51);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 128.0f);
    glCallList(51);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAIN_POST_2));
    glCallList(52);
    glPushMatrix();
    glTranslatef(128.0f, 0.0f, 0.0f);
    glCallList(52);
    glPopMatrix();
}

void DrawMainPosts() {
    tp.CreateDisplayList(XY, 18, 128.0f, 256.0f, 31740.0f, 9995.0f, 10105.0f,
                         1.0f, 4.48f);
    tp.CreateDisplayList(YZ, 19, 256.0f, 128.0f, 31740.0f, 9995.0f, 10105.0f,
                         4.48f, 1.0f);
    tp.CreateDisplayList(XY, 51, 128.0f, 256.0f, 31740.0f, 9555.0f, 8100.0f, 1.0f,
                         6.2f); // 1st by steps
    tp.CreateDisplayList(YZ, 52, 256.0f, 128.0f, 31740.0f, 9555.0f, 8100.0f, 6.2f,
                         1.0f); // 1st by steps
}

//--------------------------------------------------------------------------------------
//  Display Window and Door Posts on Phys SCi Building
//--------------------------------------------------------------------------------------
void DisplayPhysSciPosts() {
    step = 0.0f;
    for (GLuint i = 0; i < 16; i++) {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_FRONT));
        glTranslatef(0.0f, 0.0f, step);
        glCallList(36);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_RIGHT));
        glCallList(37);
        glPopMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_LEFT));
        glTranslatef(0.0f, 0.0f, step + 77.0f);
        glCallList(38);
        glPopMatrix();
        step += 960.0f;
    }

    step = 960.0f;
    for (GLuint i = 0; i < 4; i++) {
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_FRONT));
        glTranslatef(0.0f, -1024.0f, step);
        glCallList(36);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_RIGHT));
        glCallList(37);
        glPopMatrix();
        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_LEFT));
        glTranslatef(0.0f, -1024.0f, step + 77.0f);
        glCallList(38);
        glPopMatrix();
        step += 960.0f;
    }
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_FRONT));
    glTranslatef(0.0f, -1024.0f, 7718.0f);
    glCallList(36);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_RIGHT));
    glCallList(37);
    glPopMatrix();
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_PHYSSCI_LEFT));
    glTranslatef(0.0f, -1024.0f, 7718.0f + 77.0f);
    glCallList(38);
    glPopMatrix();

    // WindowLedges Phys Sci (toilets downstairs)
    step = 960.0f;
    for (GLuint i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(0.0f, -832.0f, step);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
        glCallList(16);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_TOP));
        glCallList(17);
        glPopMatrix();
        step += 1920.0f;
    }

    step       = 6758.0f;
    stepLength = -832.0f;
    for (GLuint i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(0.0f, stepLength, step);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
        glCallList(16);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_TOP));
        if (i == 1)
            glCallList(17);
        glPopMatrix();
        step += 960.0f;
        stepLength -= 256.0f;
    }
    // shops downstairs phys sci
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_BOTT));
    for (GLuint i = 40; i < 42; i++)
        glCallList(i);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
    glCallList(42);

    // WindowLedges Phys Sci (upstairs)
    step = 0.0f;
    for (GLuint i = 0; i < 15; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_FRONT));
        glCallList(16);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_PS_TOP));
        glCallList(17);
        glPopMatrix();
        step += 960.0f;
    }
}

void DrawPhysSciPosts() {
    // WINDOWPOST_PS
    tp.CreateDisplayList(YZ, 36, 512.0f, 128.0f, 33848.0f, 11347.0f, 26625.0f,
                         1.0f, 0.6016f);
    tp.CreateDisplayList(XY, 37, 64.0f, 512.0f, 33848.0f, 11347.0f, 26625.0f,
                         1.0f, 1.0f);
    tp.CreateDisplayList(XY, 38, 64.0f, 512.0f, 33848.0f, 11347.0f, 26625.0f,
                         1.0f, 1.0f);

    // WINDOWLEDGE_PS_FRONT & TOP (shorter phys sci ds)
    // first shop
    glNewList(40, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(33808.0f, 10544.0f, 33421.0f);
    glTexCoord2f(0.0, 0.9375);
    glVertex3f(33808.0f, 10544.0f, 33421.0f + (1024.0f * 0.9375f));
    glTexCoord2f(1.0f, 0.9375f);
    glVertex3f(33928.0f, 10588.0f, 33421.0f + (1024.0f * 0.9375f));
    glTexCoord2f(1.0, 0.0);
    glVertex3f(33928.0f, 10588.0f, 33421.0f);
    glEnd();
    glEndList();

    // small window
    glNewList(41, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(33808.0f, 10288.0f, 38239.0f);
    glTexCoord2f(0.0f, 0.315f);
    glVertex3f(33808.0f, 10288.0f, 38239.0f + (1024.0f * 0.315f));
    glTexCoord2f(1.0f, 0.315f);
    glVertex3f(33928.0f, 10332.0f, 38239.0f + (1024.0f * 0.315f));
    glTexCoord2f(1.0, 0.0);
    glVertex3f(33928.0f, 10332.0f, 38239.0f);
    glEnd();
    glEndList();
    tp.CreateDisplayList(YZ, 42, 32.0f, 1024.0f, 33808.0f, 10256.0f, 38239.0f,
                         1.0f, 0.315f);

    // WINDOWLEDGE_PS_FRONT & TOP
    tp.CreateDisplayList(YZ, 16, 32.0f, 1024.0f, 33808.0f, 11344.0f, 26663.0f,
                         1.0f, 0.9375f);
    glNewList(17, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(33808.0f, 11376.0f, 26663.0f);
    glTexCoord2f(0.0, 0.9375);
    glVertex3f(33808.0f, 11376.0f, 26663.0f + (1024.0f * 0.9375f));
    glTexCoord2f(1.0f, 0.9375f);
    glVertex3f(33928.0f, 11420.0f, 26663.0f + (1024.0f * 0.9375f));
    glTexCoord2f(1.0, 0.0);
    glVertex3f(33928.0f, 11420.0f, 26663.0f);
    glEnd();
    glEndList();
}

//--------------------------------------------------------------------------------------
//  Display Paving Around Shop Doorway
//--------------------------------------------------------------------------------------
void DisplayDoorPaving() {
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOORPAVE_1));
    glCallList(47);
    glCallList(48);
}

void DrawDoorPaving() {
    tp.CreateDisplayList(XZ, 47, 128.0f, 256.0f, 33808.0f, 10000.0f, 31508.0f, 0.75f,
                         7.5f); // phy sci 1st doorway
    tp.CreateDisplayList(XZ, 48, 128.0f, 256.0f, 33808.0f, 10000.0f, 35324.0f, 0.75f,
                         3.5f); // phy sci 2nd doorway
}

//--------------------------------------------------------------------------------------
// Display window and door posts of library
//--------------------------------------------------------------------------------------
void DisplayLibraryPosts() {
    stepLength = 0.0f;
    for (int j = 0; j < 2; j++) {
        glPushMatrix();
        glTranslatef(0.0f, stepLength, 0.0f);
        step = 0.0f;
        for (int i = 0; i < 15; i++) {
            if (!(i > 12 && j == 0)) {
                glPushMatrix();
                glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_FRONT));
                glTranslatef(step, 0.0f, 0.0f);
                glCallList(57);
                glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_RIGHT));
                glCallList(58);
                glPopMatrix();
                glPushMatrix();
                glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_LEFT));
                glTranslatef(step + 77.0f, 0.0f, 0.0f);
                glCallList(59);
                glPopMatrix();
                step -= 1088.0f;
            }
        }
        glPopMatrix();
        stepLength += 1054;
    }
    stepLength = 0.0f;
    for (int j = 0; j < 2; j++) {
        glPushMatrix();
        glTranslatef(0.0f, stepLength, 0.0f);
        // WINDOWLEDGE_LIB
        step = 0.0f;
        for (int i = 0; i < 13; i++) {
            if (!(i > 10 && j == 0)) {
                glPushMatrix();
                glTranslatef(step, 0.0f, 0.0f);
                glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_A));
                glCallList(60);
                glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_B));
                glCallList(61);
                glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_A));
                glCallList(62);
                glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_B));
                glCallList(63);
                glPopMatrix();
            }
            step -= 1088.0f;
        }
        glPopMatrix();
        stepLength += 1024;
    }
    // first ledge upstairs
    glPushMatrix();
    glTranslatef(1088.0f, 1024.0f, 0.0f);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_A));
    glCallList(60);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_B));
    glCallList(61);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_A));
    glCallList(62);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWLEDGE_LIB_TOP_B));
    glCallList(63);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_TOP));
    glCallList(442);
    glCallList(444);
    glCallList(446);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_EDGE));
    glCallList(445);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_EDGE_2));
    glCallList(443);
    glPushMatrix();
    glTranslatef(1152.0f, 0.0f, 0.0f);
    glCallList(443);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_COUNTER_EDGE_3));
    glCallList(447);
    glPushMatrix();
    glTranslatef(1152.0f, 0.0f, 0.0f);
    glCallList(447);
    glPopMatrix();
}

void DrawLibraryPosts() {
    // WINDOWPOST_LIB_FRONT
    tp.CreateDisplayList(XY, 57, 128.0f, 512.0f, 24035.0f, 10304.0f, 43096.0f,
                         0.6016f, 1.0f);
    tp.CreateDisplayList(YZ, 58, 512.0f, 64.0f, 24035.0f, 10304.0f, 43096.0f,
                         1.0f, 1.0f);
    tp.CreateDisplayList(YZ, 59, 512.0f, 64.0f, 24035.0f, 10304.0f, 43096.0f,
                         1.0f, 1.0f);

    // WINDOWLEDGE_LIB
    tp.CreateDisplayList(XY, 61, 1024.0f, 32.0f, 21896.0f, 10320.0f, 43056.0f,
                         0.5313f, 1.0f);
    tp.CreateDisplayList(XY, 60, 1024.0f, 32.0f, 22440.0f, 10320.0f, 43056.0f,
                         0.5313f, 1.0f);
    glNewList(62, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(21896.0f, 10352.0f, 43056.0f);
    glTexCoord2f(0.5313f, 0.0f);
    glVertex3f(21896.0f + (1024.0f * 0.5313f), 10352.0f, 43056.0f);
    glTexCoord2f(0.5313f, 1.0f);
    glVertex3f(21896.0f + (1024.0f * 0.5313f), 10396.0f, 43176.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(21896.0f, 10396.0f, 43176.0f);
    glEnd();
    glEndList();
    glNewList(63, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(22440.0f, 10352.0f, 43056.0f);
    glTexCoord2f(0.5313f, 0.0f);
    glVertex3f(22440.0f + (1024.0f * 0.5313f), 10352.0f, 43056.0f);
    glTexCoord2f(0.5313f, 1.0f);
    glVertex3f(22440.0f + (1024.0f * 0.5313f), 10396.0f, 43176.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(22440.0f, 10396.0f, 43176.0f);
    glEnd();
    glEndList();

    // Ticket Counter
    tp.CreateDisplayList(XZ, 442, 128.0f, 256.0f, 22984.0f, 10305.0f, 42992.0f,
                         9.0f, 0.625f);
    tp.CreateDisplayList(YZ, 443, 64.0f, 64.0f, 22984.0f, 10256.0f, 43056.0f,
                         0.766f, 1.0f);
    tp.CreateDisplayList(XY, 444, 128.0f, 256.0f, 22984.0f, 10256.0f, 43056.0f,
                         9.0f, 0.1914f);

    tp.CreateDisplayList(XY, 445, 128.0f, 32.0f, 22984.0f, 10286.0f, 42992.0f,
                         9.0f, 0.59f);

    tp.CreateAngledPolygon(446, 128.0f, 256.0f, 22984.0f, 24136.0f, 24136.0f,
                           22984.0f, 10286.0f, 10286.0f, 10276.0f, 10276.0f,
                           42992.0f, 42992.0f, 43088.0f, 43088.0f, 5, 1);

    tp.CreateAngledPolygon(447, 64.0f, 64.0f, 22984.0f, 22984.0f, 22984.0f,
                           22984.0f, 10286.0f, 10276.0f, 10305.0f, 10305.0f,
                           42992.0f, 43056.0f, 43056.0f, 42992.0f, 6, 1);
}

//--------------------------------------------------------------------------------------
//  Display Pavement
//--------------------------------------------------------------------------------------
void DisplayPavement() {
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
    for (GLuint i = 72; i < 74; i++)
        glCallList(i);
    glCallList(28);
    for (GLuint i = 81; i < 89; i++)
        glCallList(i);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1920.0f);
    glCallList(86);
    glPopMatrix();

    for (GLuint i = 247; i < 250; i++)
        glCallList(i);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 8640.0f);
    glCallList(248);
    glPopMatrix();
    glCallList(241);
    glCallList(428);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_TOP));
    for (GLuint i = 91; i < 93; i++)
        glCallList(i);
    glCallList(246);
    glCallList(243);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_TOP_FLIP));
    glCallList(74);
    glCallList(245);
    glCallList(244);
    glCallList(242);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENTSIDE_LEFT));
    glCallList(75);
    glCallList(436);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENTSIDE_RIGHT));
    glCallList(76);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENTSIDE_TOP));
    glCallList(77);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT));
    glCallList(78);
    glCallList(79);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_16));
    glCallList(80);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_CORNER_1));
    glCallList(93);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_CORNER_2));
    glCallList(94);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PAVEMENT_FLIP));
    for (GLuint i = 89; i < 91; i++)
        glCallList(i);
    glCallList(240);
    glPushMatrix();
    glTranslatef(-26848.0f, 0.0f, 0.0f);
    glCallList(240);
    glPopMatrix();
}

void DrawPavement() {
    // PAVEMENT
    tp.CreateDisplayList(XZ, 87, 128.0f, 64.0f, 2608.0f, 10000.0f, 10000.0f,
                         17.0f, 482.5f);
    tp.CreateDisplayList(XZ, 73, 128.0f, 64.0f, 31632.0f, 10000.0f, 10000.0f,
                         17.0f, 482.5f);
    tp.CreateDisplayList(XZ, 88, 128.0f, 64.0f, 33744.0f, 10000.0f, 41104.0f, 4.75f,
                         30.5f); // by steps between phys sci and library
    tp.CreateDisplayList(XZ, 428, 128.0f, 64.0f, 34256.0f, 10000.0f, 26704.0f, 1.0f,
                         9.5f); // phys sci doorway (behind carpet)
    //

    // PAVEMENT_TOP
    tp.CreateDisplayList(XZ, 74, 64.0f, 128.0f, 4912.0f, 10000.0f, 40880.0f,
                         416.5f, 17.0f);
    tp.CreateDisplayList(XZ, 246, 64.0f, 128.0f, 32656.0f, 10000.0f, 42928.0f, 15.0f,
                         2.0f); // gcl1 door way
    tp.CreateDisplayList(XZ, 245, 64.0f, 128.0f, 24080.0f, 10000.0f, 42928.0f, 3.0f,
                         1.5f); // gcl1 door way
    tp.CreateDisplayList(XZ, 244, 64.0f, 128.0f, 8189.0f, 10000.0f, 42928.0f, 44.8f,
                         1.80f); // library door way
    tp.CreateDisplayList(XZ, 243, 64.0f, 128.0f, 2576.0f, 10000.0f, 42928.0f, 36.0f,
                         21.0f); // entrance to IT block
    tp.CreateDisplayList(XZ, 242, 64.0f, 128.0f, 4848.0f, 10000.0f, 42928.0f, 27.5f,
                         21.0f); // entrance to IT block
    tp.CreateDisplayList(XZ, 241, 128.0f, 64.0f, 2096.0f, 10000.0f, 41168.0f, 4.5f,
                         29.0f); // entance to psch block
    tp.CreateDisplayList(XZ, 240, 128.0f, 64.0f, 31568.0f, 10000.0f, 40816.0f, 1.0f,
                         1.0f); // corner space filler

    // PAVEMENT_JOINS
    glNewList(89, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(31568.0f, 10000.0f, 40816.0f);
    glTexCoord2f(17.5, 0.0);
    glVertex3f(33808.0f, 10000.0f, 40816.0f);
    glTexCoord2f(17.5f, 35.0f);
    glVertex3f(33808.0f, 10000.0f, 43056.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(31568.0f, 10000.0f, 40816.0f);
    glEnd();
    glEndList();
    glNewList(91, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(31504.0f, 10000.0f, 40880.0f);
    glTexCoord2f(34.0, 17.0);
    glVertex3f(33680.0f, 10000.0f, 43056.0f);
    glTexCoord2f(34.0f, 17.0f);
    glVertex3f(33680.0f, 10000.0f, 43056.0f);
    glTexCoord2f(0.0, 17.0);
    glVertex3f(31504.0f, 10000.0f, 43056.0f);
    glEnd();
    glEndList();
    glNewList(93, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(31504.0f, 10000.0f, 40880.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(31632.0f, 10000.0f, 40880.0f);
    glTexCoord2f(18.0f, 17.0f);
    glVertex3f(33808.0f, 10000.0f, 43056.0f);
    glTexCoord2f(17.0f, 17.0f);
    glVertex3f(33680.0f, 10000.0f, 43056.0f);
    glEnd();
    glEndList();

    glNewList(90, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2608.0f, 10000.0f, 40816.0f);
    glTexCoord2f(17.5f, 0.0f);
    glVertex3f(4848.0f, 10000.0f, 40816.0f);
    glTexCoord2f(17.5f, 0.0f);
    glVertex3f(4848.0f, 10000.0f, 40816.0f);
    glTexCoord2f(0.0f, 35.0f);
    glVertex3f(2608.0f, 10000.0f, 43056.0f);
    glEnd();
    glEndList();

    glNewList(92, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4912.0f, 10000.0f, 40880.0f);
    glTexCoord2f(34.0, 17.0);
    glVertex3f(2736.0f, 10000.0f, 43056.0f);
    glTexCoord2f(34.0f, 17.0f);
    glVertex3f(2736.0f, 10000.0f, 43056.0f);
    glTexCoord2f(0.0f, 17.0f);
    glVertex3f(4912.0f, 10000.0f, 43056.0f);
    glEnd();
    glEndList();

    glNewList(94, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(17.0f, 0.0f);
    glVertex3f(4784.0f, 10000.0f, 40880.0f);
    glTexCoord2f(18.0f, 0.0f);
    glVertex3f(4912.0f, 10000.0f, 40880.0f);
    glTexCoord2f(1.0f, 17.0f);
    glVertex3f(2736.0f, 10000.0f, 43056.0f);
    glTexCoord2f(0.0f, 17.0f);
    glVertex3f(2608.0f, 10000.0f, 43056.0f);
    glEnd();
    glEndList();

    // PAVEMENTSIDE_LEFT
    tp.CreateDisplayList(XZ, 75, 64.0f, 64.0f, 31568.0f, 10000.0f, 10096.0f,
                         1.0f, 480.0f);
    tp.CreateDisplayList(XZ, 436, 64.0f, 64.0f, 31568.0f, 9086.0f, 3408.0f, 1.0f,
                         45.0f); // Side paving at entrance
    // PAVEMENTSIDE_RIGHT
    tp.CreateDisplayList(XZ, 76, 64.0f, 64.0f, 4784.0f, 10000.0f, 10000.0f,
                         1.0f, 481.5f);
    // PAVEMENTSIDE_TOP
    tp.CreateDisplayList(XZ, 77, 64.0f, 64.0f, 4848.0f, 10000.0f, 40816.0f,
                         417.5f, 1.0f);
    // PAVEMENT_STEPS_CORNER
    tp.CreateDisplayList(XZ, 78, 128.0f, 64.0f, 31568.0f, 10000.0f, 10000.0f, 1.0f,
                         1.5f); // corner above chanc steps
    tp.CreateDisplayList(XZ, 80, 32.0f, 64.0f, 31568.0f, 10000.0f, 9950.0f, 70.0f,
                         0.797f); // strip along top of chanc steps
    tp.CreateDisplayList(XZ, 28, 128.0f, 64.0f, 33744.0f, 10000.0f, 22096.0f, 17.2f,
                         52.0f); // between chanc and phy sci
    tp.CreateDisplayList(XZ, 248, 128.0f, 64.0f, 33744.0f, 10000.0f, 10449.0f, 1.5f,
                         16.0f); // doorway to chanc
    tp.CreateDisplayList(XZ, 247, 128.0f, 64.0f, 33744.0f, 10000.0f, 39185.0f, 1.5f,
                         23.0f); // doorway to red posts
    tp.CreateDisplayList(XZ, 249, 128.0f, 64.0f, 31632.0f, 9086.0f, 3408.0f, 18.0f,
                         45.0f); // entry (bottom of steps)
    tp.CreateDisplayList(XZ, 81, 128.0f, 64.0f, 33744.0f, 10000.0f, 26704.0f, 2.5f,
                         11.0f); // phys sci doorway 1
    tp.CreateDisplayList(XZ, 82, 128.0f, 64.0f, 33744.0f, 10000.0f, 27344.0f, 4.5f,
                         3.5f); // phys sci doorway 1
    tp.CreateDisplayList(XZ, 83, 128.0f, 64.0f, 33744.0f, 10000.0f, 36304.0f, 5.0f,
                         5.3f); // phys sci doorway 2
    tp.CreateDisplayList(XZ, 84, 128.0f, 64.0f, 33744.0f, 10000.0f, 36624.0f, 2.5f,
                         9.0f); // phys sci doorway 2
    tp.CreateDisplayList(XZ, 85, 128.0f, 64.0f, 33744.0f, 10000.0f, 37200.0f, 5.0f,
                         10.5f); // phys sci doorway 2
    tp.CreateDisplayList(XZ, 86, 128.0f, 64.0f, 33744.0f, 10000.0f, 28624.0f, 2.5f,
                         13.5f); // phys sci toilet doorways
}

//--------------------------------------------------------------------------------------
// Display Wall Bricks
//--------------------------------------------------------------------------------------

void DisplayBricks() {
    // WALL_BRICK_YZ
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ));
    for (GLuint i = 101; i < 111; i++)
        glCallList(i);
    for (GLuint i = 112; i < 126; i++)
        glCallList(i);
    for (GLuint i = 191; i < 195; i++)
        glCallList(i);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1920.0f);
    glCallList(109);
    glCallList(110);
    glCallList(394);
    glPopMatrix();
    glCallList(222);
    glCallList(394);
    glCallList(396);
    glCallList(397);

    // bricks with security sign
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_SEC_SIGN));
    glCallList(398);

    // WALL_BRICK_USD_YZ
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_USD_YZ));
    for (GLuint i = 200; i < 202; i++)
        glCallList(i);
    glCallList(188);

    // WALL_BRICK_XY
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY));
    for (GLuint i = 135; i < 165; i++)
        glCallList(i);
    for (GLuint i = 217; i < 222; i++)
        glCallList(i);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1792.0f);
    glCallList(136);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 1024.0f, 0.0f);
    glCallList(152);
    glPopMatrix();
    for (GLuint i = 195; i < 198; i++)
        glCallList(i);
    glCallList(392);
    for (GLuint i = 430; i < 434; i++)
        glCallList(i);
    // Brick with map on
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MAP_2));
    glCallList(434);

    // WALL_BRICK_GAP_YZ
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_GAP_YZ));
    for (GLuint i = 180; i < 182; i++)
        glCallList(i);
    glPushMatrix();
    glTranslatef(0.0f, 1024.0f, 0.0f);
    glCallList(180);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1920.0f);
    glCallList(181);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_GAP2_YZ));
    glCallList(182);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_GAP_1));
    for (GLuint i = 183; i < 185; i++)
        glCallList(i);

    // WALL_BRICK_XY_END
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY_END));
    for (GLuint i = 165; i < 168; i++)
        glCallList(i);
    glCallList(134);
    glCallList(185);
    glCallList(187);
    glCallList(399);
    glPushMatrix();
    glTranslatef(-32.0f, 0.0f, 640.0f);
    glCallList(399);
    glPopMatrix();
    step = -832.0f;
    for (GLuint i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(166);
        glPopMatrix();
        step += 1920.0f;
    }
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 321.0f);
    glCallList(167);
    glPopMatrix();
    for (GLuint i = 131; i < 132; i++)
        glCallList(i);
    glCallList(132);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 960.0f);
    glCallList(132);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 8640.0f);
    glCallList(132);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 9600.0f);
    glCallList(132);
    glPopMatrix();
    glCallList(133);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_XY_87WIDTH));
    glCallList(130);
    glCallList(186);

    // WALL_BRICK_YZ_END
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_YZ_END));
    for (GLuint i = 126; i < 130; i++)
        glCallList(i);
    glPushMatrix();
    glTranslatef(-896.0f, 0.0f, 0.0f);
    glCallList(128);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 1088.0f, 0.0f);
    glCallList(129);
    glCallList(168);
    glPopMatrix();
    for (GLuint i = 168; i < 170; i++)
        glCallList(i);
    glCallList(390);
    glCallList(391);
    glCallList(393);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_3_4));
    glCallList(189);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SHADOW_BRICK));
    glCallList(190);
}

void DrawBricks() {
    // WALL_BRICK_YZ
    // --------  (Face of Cancerllary Building) --------
    tp.CreateDisplayList(YZ, 101, 128.0f, 128.0f, 33808.0f, 9872.0f, 9552.0f, 2.5f,
                         7.5f); // panel 1 (above steps)
    tp.CreateDisplayList(YZ, 222, 128.0f, 128.0f, 33840.0f, 8976.0f, 5840.0f,
                         23.625f,
                         5.0f); // panel 1 (before steps)
    tp.CreateDisplayList(YZ, 102, 128.0f, 128.0f, 33808.0f, 8976.0f, 6480.0f,
                         23.625f,
                         24.0f); // panel 2 (below steps)
    tp.CreateDisplayList(YZ, 103, 128.0f, 128.0f, 33808.0f, 10000.0f, 11472.0f, 1.5f,
                         60.0f); // panel 3 (below window 1)
    tp.CreateDisplayList(YZ, 104, 128.0f, 128.0f, 33808.0f, 10000.0f, 20112.0f, 1.5f,
                         15.5f); // panel 4 (below window 2)
    tp.CreateDisplayList(YZ_FLIP, 105, 128.0f, 128.0f, 33808.0f, 10960.0f,
                         9552.0f, 2.0f, 97.5f); // us panel 4
    tp.CreateDisplayList(YZ, 120, 128.0f, 128.0f, 33808.0f, 10960.0f, 22032.0f, 2.0f,
                         0.5f); // us panel 4 (last 1/2 brick)

    // -------- (Face of Physical Science/Shops Block) --------
    tp.CreateDisplayList(YZ, 106, 128.0f, 128.0f, 33808.0f, 10000.0f, 25344.0f,
                         4.525f, 11.0f); // panel 1 (around rusty man)
    tp.CreateDisplayList(YZ, 107, 128.0f, 128.0f, 33808.0f, 11024.0f, 25344.0f, 6.5f,
                         10.0f); // us panel 1
    tp.CreateDisplayList(YZ, 108, 128.0f, 128.0f, 33808.0f, 11024.0f, 26624.0f, 2.5f,
                         113.305f); // us panel 2
    tp.CreateDisplayList(YZ, 109, 128.0f, 128.0f, 33808.0f, 10000.0f, 27559.0f, 3.5f,
                         8.5f); // panel 3 (toilets window)
    tp.CreateDisplayList(YZ, 394, 128.0f, 128.0f, 33808.0f, 10384.0f, 27559.0f, 1.0f,
                         7.5f); // panel 3 (toilets window)
    tp.CreateDisplayList(YZ, 110, 128.0f, 128.0f, 33872.0f, 9936.0f, 28967.0f, 6.5f,
                         4.5f); // panel 4 (toilets door)
    tp.CreateDisplayList(YZ, 112, 128.0f, 128.0f, 33808.0f, 10000.0f, 33422.0f, 2.0f,
                         14.4f); // panel 5 (booth)
    tp.CreateDisplayList(YZ, 113, 128.0f, 128.0f, 33808.0f, 10128.0f, 33422.0f, 3.0f,
                         5.5f); // panel 5 (booth below window)
    tp.CreateDisplayList(YZ, 188, 128.0f, 128.0f, 33808.0f, 10128.0f, 34254.0f, 3.0f,
                         1.0f); // panel 5 (booth below window)
    tp.CreateDisplayList(YZ, 115, 128.0f, 128.0f, 34260.0f, 10000.0f, 36319.0f, 2.5f,
                         2.5f); // panel 6 (phys sci doorway)
    tp.CreateDisplayList(YZ, 191, 128.0f, 128.0f, 34260.0f, 10256.0f, 36319.0f, 4.5f,
                         1.5f); // panel 6 (phys sci doorway)
    tp.CreateDisplayList(YZ, 192, 128.0f, 128.0f, 34260.0f, 10576.0f, 36383.0f, 2.0f,
                         2.0f); // panel 6 (phys sci doorway)
    tp.CreateDisplayList(YZ, 114, 128.0f, 128.0f, 33808.0f, 10000.0f, 37855.0f,
                         2.05f,
                         10.51f); // panel 7 (with window)
    tp.CreateDisplayList(YZ, 116, 128.0f, 128.0f, 33808.0f, 10128.0f, 37855.0f, 5.5f,
                         1.05f); // panel 7 (with window)
    tp.CreateDisplayList(YZ, 396, 128.0f, 128.0f, 33808.0f, 10128.0f, 38111.0f, 5.5f,
                         1.0f); // panel 7 (with window)
    tp.CreateDisplayList(YZ, 397, 128.0f, 128.0f, 33808.0f, 10512.0f, 37855.0f, 2.5f,
                         3.0f); // panel 7 (with window)
    tp.CreateDisplayList(YZ, 398, 256.0f, 128.0f, 33808.0f, 10256.0f, 37983.0f,
                         1.05f,
                         1.1f); // panel 7 (with sign)
    tp.CreateDisplayList(YZ_FLIP, 117, 128.0f, 128.0f, 33808.0f, 10128.0f,
                         38560.0f, 5.5f, 0.5f); // panel 7 (with window)
    tp.CreateDisplayList(YZ, 118, 128.0f, 128.0f, 33808.0f, 10128.0f, 38624.0f, 5.5f,
                         4.5f); // panel 7 (with window)
    tp.CreateDisplayList(YZ, 119, 128.0f, 128.0f, 33808.0f, 10000.0f, 40615.0f, 6.5f,
                         4.0f); // panel 8 (end panel)
    tp.CreateDisplayList(YZ, 121, 128.0f, 128.0f, 34256.0f, 9936.0f, 27303.0f, 3.0f,
                         2.0f); // first doorway panel
    tp.CreateDisplayList(YZ, 193, 128.0f, 128.0f, 34256.0f, 10576.0f, 27303.0f, 2.0f,
                         2.0f); // first doorway panel
    tp.CreateDisplayList(YZ, 194, 128.0f, 128.0f, 34256.0f, 10192.0f, 27431.0f, 3.5f,
                         1.0f); // first doorway panel

    // -------- (Face of Canteen Block) --------
    tp.CreateDisplayList(YZ, 122, 128.0f, 128.0f, 2608.0f, 10000.0f, 10000.0f, 7.0f,
                         243.5f); // long downstairs panel
    tp.CreateDisplayList(YZ, 123, 128.0f, 128.0f, 2608.0f, 10000.0f, 42960.0f, 7.0f,
                         21.0f); // end downstairs panel
    tp.CreateDisplayList(YZ, 124, 128.0f, 128.0f, 2608.0f, 11088.0f, 10000.0f, 7.0f,
                         278.5f); // long upstairs panel
    tp.CreateDisplayList(XY, 136, 128.0f, 128.0f, 2096.0f, 10000.0f, 42960.0f, 4.0f,
                         7.0f); // corner exit to psc block from canteen

    // WALL_BRICK_USD_YZ
    tp.CreateDisplayList(YZ, 200, 128.0f, 128.0f, 33808.0f, 10576.0f, 25344.0f, 2.0f,
                         1.0f); // panel 1 (around rusty man)
    tp.CreateDisplayList(YZ, 201, 128.0f, 128.0f, 33808.0f, 10576.0f, 26496.0f, 2.0f,
                         2.0f); // panel 1 (around rusty man)

    // WALL_BRICK_XY
    // --------  (Cancerllary Building) --------
    tp.CreateDisplayList(XY, 399, 128.0f, 128.0f, 33840.0f, 8976.0f, 5840.0f, 0.5f,
                         23.625f); // first corner edge (bottom of steps)
    tp.CreateDisplayList(XY, 130, 128.0f, 128.0f, 33808.0f, 10960.0f, 22096.0f,
                         0.68f,
                         2.0f); // below us window (end wall)
    tp.CreateDisplayList(XY, 131, 128.0f, 128.0f, 33808.0f, 10192.0f, 9552.0f, 0.68f,
                         15.5f); // above steps
    tp.CreateDisplayList(XY, 132, 128.0f, 128.0f, 33808.0f, 10000.0f, 10512.0f,
                         0.68f,
                         1.5f); // first door (others)
    tp.CreateDisplayList(XY, 133, 128.0f, 128.0f, 33808.0f, 11344.0f, 26624.0f,
                         0.68f,
                         4.0f); // next us window phys sci
    tp.CreateDisplayList(XY, 143, 128.0f, 128.0f, 33895.0f, 10000.0f, 22096.0f,
                         15.5f,
                         16.0f); // end wall
    tp.CreateDisplayList(XY, 186, 128.0f, 128.0f, 33808.0f, 10000.0f, 22096.0f,
                         0.68f,
                         1.5f); // end wall
    // --------  (Phys Science Block) -------
    tp.CreateDisplayList(XY, 197, 128.0f, 128.0f, 33808.0f, 10640.0f, 25344.0f, 1.5f,
                         1.5f); // end wall above telephones
    tp.CreateDisplayList(XY, 196, 128.0f, 128.0f, 33936.0f, 10640.0f, 25344.0f, 6.0f,
                         1.505f); // end wall above telephones
    tp.CreateDisplayList(XY, 195, 128.0f, 128.0f, 34576.0f, 10128.0f, 25344.0f, 1.0f,
                         6.5f); // next to telephones
    tp.CreateDisplayList(XY, 190, 128.0f, 128.0f, 34704.0f, 10000.0f, 25344.0f, 9.5f,
                         5.75f); // end wall behind drinks machine
    tp.CreateDisplayList(XY, 189, 128.0f, 128.0f, 34704.0f, 10736.0f, 25344.0f, 9.5f,
                         0.75f); // end wall above drinks machine
    tp.CreateDisplayList(XY, 144, 128.0f, 128.0f, 33808.0f, 10000.0f, 25344.0f, 7.0f,
                         1.6f); // end wall
    tp.CreateDisplayList(XY, 145, 128.0f, 128.0f, 33876.0f, 9936.0f, 36319.0f, 3.0f,
                         7.0f); // ps 2nd door(leftside entrance)
    tp.CreateDisplayList(XY, 146, 128.0f, 128.0f, 33808.0f, 9936.0f, 37855.0f, 4.25f,
                         7.0f); // ps 2nd door(rightside entrance)
    tp.CreateDisplayList(XY, 147, 128.0f, 128.0f, 33808.0f, 9936.0f, 26752.0f, 4.0f,
                         7.0f); // ps first door (left bottom)
    tp.CreateDisplayList(XY, 148, 128.0f, 128.0f, 33808.0f, 9936.0f, 27559.0f, 3.5f,
                         4.5f); // ps first door (right bottom)
    tp.CreateDisplayList(XY, 149, 128.0f, 128.0f, 33872.0f, 10384.0f, 27559.0f, 3.0f,
                         3.5f); // ps first door (right top)
    tp.CreateDisplayList(XY, 185, 128.0f, 128.0f, 34256.0f, 10000.0f, 27303.0f, 0.5f,
                         6.5f); // ps first door (1/2 inner brick)
    tp.CreateDisplayList(XY, 166, 128.0f, 128.0f, 33808.0f, 10000.0f, 29479.0f, 0.5f,
                         4.0f); // side of toilet doors phys sci
    tp.CreateDisplayList(XY, 167, 128.0f, 128.0f, 33808.0f, 10256.0f, 38239.0f,
                         0.75f,
                         4.5f); // side of small window phys sci
    tp.CreateDisplayList(XY_FLIP, 152, 128.0f, 128.0f, 33936.0f, 10832.0f,
                         25344.0f, 15.5f, 2.5f); // end wall panel 2 phys sci
    tp.CreateDisplayList(XY, 153, 128.0f, 128.0f, 33808.0f, 11024.0f, 25344.0f,
                         17.5f,
                         6.5f); // end wall panel 3 phys sci
    tp.CreateDisplayList(XY, 165, 128.0f, 128.0f, 34260.0f, 10000.0f, 36639.0f, 0.7f,
                         6.5f); // ps 2nd door(inner 1/2 brick)
    tp.CreateDisplayList(XY, 187, 128.0f, 128.0f, 33808.0f, 10256.0f, 34382.0f, 0.5f,
                         2.0f); // side of toilet doors phys sci

    // --------  (Library Block) --------
    tp.CreateDisplayList(XY, 154, 128.0f, 128.0f, 33616.0f, 10000.0f, 43056.0f,
                         19.0f,
                         6.0f); // first panel
    tp.CreateDisplayList(XY, 155, 128.0f, 128.0f, 30800.0f, 10000.0f, 43056.0f,
                         15.0f,
                         6.0f); // 2nd panel
    tp.CreateDisplayList(XY, 156, 128.0f, 128.0f, 27976.0f, 9936.0f, 43056.0f, 12.0f,
                         3.0f); // 3rd panel (next to KBLT)
    tp.CreateDisplayList(XY, 217, 128.0f, 128.0f, 29512.0f, 9936.0f, 43056.0f, 10.0f,
                         2.75f); // 3rd panel (below nexus sign)
    tp.CreateDisplayList(XY, 157, 128.0f, 128.0f, 24264.0f, 10256.0f, 43056.0f, 1.5f,
                         4.0f); // 4th panel (next to KBLT)
    tp.CreateDisplayList(XY, 218, 128.0f, 128.0f, 24264.0f, 10000.0f, 43056.0f,
                         11.5f,
                         2.5f); // around glass boards
    tp.CreateDisplayList(XY, 219, 128.0f, 128.0f, 25352.0f, 10192.0f, 43056.0f, 3.0f,
                         4.5f); // around glass boards
    tp.CreateDisplayList(XY, 220, 128.0f, 128.0f, 27976.0f, 10192.0f, 43056.0f, 3.0f,
                         4.5f); // around glass boards
    tp.CreateDisplayList(XY, 221, 128.0f, 128.0f, 29256.0f, 10192.0f, 43056.0f, 2.0f,
                         4.5f); // around glass boards
    tp.CreateDisplayList(XY, 158, 128.0f, 128.0f, 30800.0f, 11024.0f, 43056.0f,
                         41.0f,
                         6.5f); // US 1st panel
    tp.CreateDisplayList(XY, 159, 128.0f, 128.0f, 24264.0f, 11024.0f, 43056.0f,
                         51.0f,
                         6.5f); // US 2nd panel
    tp.CreateDisplayList(XY, 160, 128.0f, 128.0f, 22984.0f, 10000.0f, 43056.0f, 9.0f,
                         2.0f); // US 3rd panel (start of ds library)
    tp.CreateDisplayList(XY, 161, 128.0f, 128.0f, 10952.0f, 10000.0f, 43056.0f,
                         94.0f,
                         2.5f); // US 4th panel (under of ds library)
    tp.CreateDisplayList(XY, 162, 128.0f, 128.0f, 6600.0f, 11024.0f, 43056.0f,
                         137.0f,
                         2.5f); // US 4th panel (under of ds library)
    tp.CreateXtoYWindowList(434, 43056.0, 6856.0, 256.0, 10256.0, 512.0, 1.0,
                            1.0); // End of DS (Map)
    tp.CreateDisplayList(XY, 433, 128.0f, 128.0f, 7112.0f, 10640.0f, 43056.0f, 8.0f,
                         1.0f); // End DS
    tp.CreateDisplayList(XY, 432, 128.0f, 128.0f, 7112.0f, 10128.0f, 43056.0f, 1.5f,
                         5.0f); // End DS
    tp.CreateDisplayList(XY, 431, 128.0f, 128.0f, 8072.0f, 10064.0f, 43056.0f,
                         0.914f,
                         5.5f); // End DS
    tp.CreateDisplayList(XY, 430, 128.0f, 128.0f, 6600.0f, 10128.0f, 43056.0f, 2.0f,
                         5.0f); // End DS
    tp.CreateDisplayList(XY, 163, 128.0f, 128.0f, 6600.0f, 10000.0f, 43056.0f,
                         12.414f, 2.0f); // End DS
    tp.CreateDisplayList(XY, 164, 128.0f, 128.0f, 6600.0f, 11024.0f, 43056.0f,
                         17.29f,
                         6.5f); // End US
    tp.CreateDisplayList(YZ, 126, 128.0f, 128.0f, 6600.0f, 10000.0f, 43056.0f, 6.0f,
                         0.5f); // end panel corner
    tp.CreateDisplayList(YZ, 125, 128.0f, 128.0f, 6514.0f, 10000.0f, 43120.0f, 14.5f,
                         20.5f); // end panel
    tp.CreateDisplayList(YZ, 127, 128.0f, 128.0f, 6600.0f, 11024.0f, 43056.0f, 6.5f,
                         0.5f); // end panel top
    tp.CreateDisplayList(YZ, 128, 128.0f, 128.0f, 33616.0f, 9936.0f, 43056.0f, 6.5f,
                         0.75f); // cgl1 side panel
    tp.CreateDisplayList(YZ, 129, 128.0f, 128.0f, 24264.0f, 9936.0f, 43056.0f, 6.5f,
                         0.5f); // gap in middle of library
    tp.CreateDisplayList(YZ, 168, 128.0f, 128.0f, 24136.0f, 9936.0f, 43056.0f, 2.5f,
                         0.5f); // gap in middle of library
    tp.CreateDisplayList(YZ, 169, 128.0f, 128.0f, 8813.12f, 11344.0f, 43056.0f, 4.0f,
                         0.5f); // edge of first us window post
    tp.CreateDisplayList(XY, 135, 128.0f, 128.0f, 24072.0f, 10000.0f, 43120.0f, 1.5f,
                         17.0f); // middle of gap
    tp.CreateDisplayList(XY, 134, 128.0f, 128.0f, 6514.0f, 10000.0f, 43120.0f, 0.75f,
                         14.5f); // end corner
    tp.CreateDisplayList(XY, 141, 128.0f, 128.0f, 33104.0f, 10000.0f, 43152.0f, 1.0f,
                         6.0f); // brick between gcl1 doors
    tp.CreateDisplayList(XY, 140, 128.0f, 128.0f, 34448.0f, 9424.0f, 43056.0f, 12.5f,
                         4.5f); // end below stairs
    tp.CreateDisplayList(YZ, 390, 128.0f, 128.0f, 10952.0f, 10000.0f, 43056.0f, 2.5f,
                         0.75f); // side of library door
    tp.CreateDisplayList(YZ, 391, 128.0f, 128.0f, 8189.0f, 10000.0f, 43056.0f, 6.0f,
                         0.5f); // side of library door
    tp.CreateDisplayList(XY, 392, 128.0f, 128.0f, 10952.0f, 10320.0f, 43152.0f,
                         0.25f,
                         3.5f); // side edge of library door

    // --------  (Phys Sci Building very end wall by steps) --------
    tp.CreateDisplayList(XY, 142, 128.0f, 128.0f, 33808.0f, 10000.0f, 41127.0f,
                         11.5f, 6.5f);
    tp.CreateDisplayList(XY, 150, 128.0f, 128.0f, 33808.0f, 11024.0f, 41127.0f,
                         16.5f, 2.5f);
    tp.CreateDisplayList(XY, 151, 128.0f, 128.0f, 34448.0f, 9360.0f, 41127.0f, 6.5f,
                         5.5f); // below window
    tp.CreateDisplayList(XY, 137, 128.0f, 128.0f, 35280.0f, 9296.0f, 41127.0f, 6.0f,
                         6.5f); // below window
    tp.CreateDisplayList(XY, 138, 128.0f, 128.0f, 35600.0f, 10000.0f, 41127.0f,
                         3.5f, 6.5f);
    tp.CreateDisplayList(XY, 139, 128.0f, 128.0f, 33872.0f, 11216.0f, 41127.0f,
                         12.5f, 6.0f);
    tp.CreateDisplayList(YZ_FLIP, 393, 128.0f, 128.0f, 33872.0f, 11344.0f,
                         41063.0f, 4.0f, 0.5f); // upstairs edge of window

    // WALL_BRICK_GAP_YZ
    tp.CreateDisplayList(YZ, 180, 128.0f, 32.0f, 33895.0f, 10192.0f, 22079.0f, 5.0f,
                         0.530f); // end chanc
    tp.CreateDisplayList(YZ, 181, 128.0f, 32.0f, 33872.0f, 10512.0f, 30542.0f, 2.5f,
                         0.80f); // toilets phys sci
    // WALL_BRICK_GAP2_YZ
    tp.CreateDisplayList(YZ, 182, 128.0f, 32.0f, 33872.0f, 10512.0f, 27559.0f, 2.5f,
                         0.80f); // toilets phys sci
    // WALL_GAP_1
    tp.CreateDisplayList(XY, 183, 8.0f, 128.0f, 30792.0f, 10000.0f, 43056.0f, 1.0f,
                         6.0f); // near KBLT
    tp.CreateDisplayList(XY, 184, 8.0f, 128.0f, 30792.0f, 11024.0f, 43056.0f, 1.0f,
                         6.5f); // as above but upstairs
}

//--------------------------------------------------------------------------------------
// Display Roof
//--------------------------------------------------------------------------------------
void DisplayRoof() {
    // main roof planks
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_PLANKS));
    for (GLuint i = 250; i < 253; i++)
        glCallList(i);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_1));
    // corner beams
    for (GLuint i = 1; i < 6; i++)
        glCallList(i);
    step = -1689.0f;
    for (GLuint i = 0; i < 85; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(253);
        glPopMatrix();
        step += 386.0f;
    }
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -2005.0f);
    glCallList(253);
    glPopMatrix();
    glCallList(254);

    step = 214.0f;
    for (GLuint i = 0; i < 8; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(254);
        glPopMatrix();
        step += 386.0f;
    }

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3216.0f);
    glCallList(254);
    glPopMatrix();

    // Beams between library and phys sci
    step = 0.0f;
    for (GLuint i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(298);
        glPopMatrix();
        step += 386.0f;
    }

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -99.0f);
    glCallList(298);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1798.0f);
    glCallList(298);
    glPopMatrix();

    // Library Roof
    step = 281.0f;
    for (GLuint i = 0; i < 70; i++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);
        glCallList(296);
        glPopMatrix();
        step += 388.0f;
    }

    // spacers
    for (GLuint i = 202; i < 204; i++)
        glCallList(i);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_4));
    for (GLuint i = 6; i < 11; i++) {
        glCallList(i);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 32.0f);
        glCallList(i);
        glPopMatrix();
    }

    step = -1689.0f;
    for (GLuint i = 0; i < 85; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(255);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step + 32.0f);
        glCallList(255);
        glPopMatrix();
        step += 386.0f;
    }

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -2005.0f);
    glCallList(255);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1973.0f);
    glCallList(255);
    glPopMatrix();

    step = 214.0f;
    for (GLuint i = 0; i < 8; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(256);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step + 32.0f);
        glCallList(256);
        glPopMatrix();
        step += 386.0f;
    }

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3216.0f);
    glCallList(256);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 32.0f);
    glCallList(256);
    glPopMatrix();

    // Beams between library and phys sci
    step = 0.0f;
    for (GLuint i = 0; i < 5; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(299);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step + 32.0f);
        glCallList(299);
        glPopMatrix();
        step += 386.0f;
    }

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -67.0f);
    glCallList(299);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1798.0f);
    glCallList(299);
    glPopMatrix();

    // Library Roof
    step = 281.0f;
    for (GLuint i = 0; i < 70; i++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);
        glCallList(297);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(step + 32.0f, 0.0f, 0.0f);
        glCallList(297);
        glPopMatrix();

        step += 388.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_PLANKS_2));
    glCallList(257);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_3));
    // corner beams
    for (GLuint i = 170; i < 175; i++) {
        glCallList(i + 5);
        glPushMatrix();
        glTranslatef(32.0f, 0.0f, 0.0f);
        glCallList(i + 5);
        glPopMatrix();
    }
    glCallList(426);
    glCallList(427);
    glPushMatrix();
    glTranslatef(0.0f, 49.0f, 3248.0f);
    glCallList(427);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 49.0f, 19031.0f);
    glCallList(427);
    glPopMatrix();

    // spacer top of chanc
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_3_TOP));
    glCallList(204);
    glCallList(205);
    glPushMatrix();
    glTranslatef(64.0f, 0.0f, 0.0f);
    glCallList(205);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_BEAM_2));
    // spacers
    for (GLuint i = 97; i < 101; i++) {
        glCallList(i);
    }
    // corner beams
    for (GLuint i = 170; i < 175; i++) {
        glCallList(i);
    }

    // Top of Roof
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_TOP));
    for (GLuint i = 214; i < 216; i++) {
        glCallList(i);
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ROOF_TOP_LIB));
    glCallList(216);
}

void DrawRoof() {
    // Chanc Top of Roof
    glNewList(214, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(31740.0f, 11364.0f, 8100.0f);
    glTexCoord2f(0.0f, 257.9f);
    glVertex3f(31740.0f, 11364.0f, 8100.0f + (128.0f * 257.9f));
    glTexCoord2f(2.0f, 273.4f);
    glVertex3f(33848.0f, 12140.72f, 8100.0f + (128.0f * 273.4f));
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(33848.0f, 12140.72f, 8100.0f);
    glEnd();
    glEndList();
    // Canteen Top of Roof
    glNewList(215, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(2608.0f, 12140.72f, 8100.0f);
    glTexCoord2f(0.0f, 273.4f);
    glVertex3f(2608.0f, 12140.72f, 8100.0f + (128.0f * 273.4f));
    glTexCoord2f(2.0f, 257.9f);
    glVertex3f(4716.0f, 11364.0f, 8100.0f + (128.0f * 257.9f));
    glTexCoord2f(2.0f, 0.0f);
    glVertex3f(4716.0f, 11364.0f, 8100.0f);
    glEnd();
    glEndList();
    // Library Top of Roof
    glNewList(216, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4716.0f, 11364.0f, 40983.2f);
    glTexCoord2f(211.125f, 0.0f);
    glVertex3f(4716.0f + (128.0f * 211.125f), 11364.0f, 40983.2f);
    glTexCoord2f(227.59f, 16.15f);
    glVertex3f(4716.0f + (128.0f * 227.59f), 12140.72f, 43095.2f);
    glTexCoord2f(-16.47f, 16.15f);
    glVertex3f(2608.0f, 12140.72f, 43095.2f);
    glEnd();
    glEndList();
    // Chanc Side Planks
    glNewList(250, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(31868.0f, 11366.0f, 8100.0f);
    glTexCoord2f(0.0f, 257.9f);
    glVertex3f(31868.0f, 11366.0f, 8100.0f + (128.0f * 257.9f));
    glTexCoord2f(16.48f, 273.4f);
    glVertex3f(33848.0f, 12094.72f, 8100.0f + (128.0f * 273.4f));
    glTexCoord2f(16.48f, 0.0f);
    glVertex3f(33848.0f, 12094.72f, 8100.0f);
    glEnd();
    glEndList();
    // Chanc Side Beams Bottom
    glNewList(253, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(31868.0f, 11284.0f, 10105.0f);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(31868.0f, 11284.0f, 10137.0f);
    glTexCoord2f(16.48f, 1.0f);
    glVertex3f(33848.0f, 12012.72f, 10137.0f);
    glTexCoord2f(16.48f, 0.0f);
    glVertex3f(33848.0f, 12012.72f, 10105.0f);
    glEnd();
    glEndList();
    // Chanc Side Beams Side
    glNewList(255, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(31868.0f, 11284.0f, 10105.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(31868.0f, 11284.0f + 82.0f, 10105.0f);
    glTexCoord2f(16.48f, 1.0f);
    glVertex3f(33848.0f, 12012.72f + 82.0f, 10105.0f);
    glTexCoord2f(16.48f, 0.0f);
    glVertex3f(33848.0f, 12012.72f, 10105.0f);
    glEnd();
    glEndList();
    // Chanc Side Planks (between chanc and phys sci)
    glNewList(251, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(35748.0f, 11366.0f, 22046.0f);
    glTexCoord2f(0.0f, 25.79f);
    glVertex3f(35748.0f, 11366.0f, 22046.0f + (128.0f * 25.79f));
    glTexCoord2f(15.82f, 25.79f);
    glVertex3f(33848.0f, 12065.28f, 22046.0f + (128.0f * 25.79f));
    glTexCoord2f(15.82f, 0.0f);
    glVertex3f(33848.0f, 12065.28f, 22046.0f);
    glEnd();
    glEndList();
    // Chanc Side Beams Bottom (between phys sci and chanc)
    glNewList(254, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(35748.0f, 11284.0f, 22096.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(35748.0f, 11284.0f, 22096.0f + 32.0f);
    glTexCoord2f(15.82f, 1.0f);
    glVertex3f(33848.0f, 11983.28f, 22096.0f + 32.0f);
    glTexCoord2f(15.82f, 0.0f);
    glVertex3f(33848.0f, 11983.28f, 22096.0f);
    glEnd();
    glEndList();
    // Chanc Side Beams Side (between phys sci and chanc)
    glNewList(256, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(35748.0f, 11284.0f, 22096.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(35748.0f, 11284.0f + 82.0f, 22096.0f);
    glTexCoord2f(15.82f, 1.0f);
    glVertex3f(33848.0f, 11983.28f + 82.0f, 22096.0f);
    glTexCoord2f(15.82f, 0.0f);
    glVertex3f(33848.0f, 11983.28f, 22096.0f);
    glEnd();
    glEndList();
    // Chanc Side Planks (between phys sci and library)
    glNewList(252, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(36108.0f, 11019.68f, 41127.0f);
    glTexCoord2f(0.0f, 15.1f);
    glVertex3f(36108.0f, 11019.68f, 41127.0f + (128.0f * 15.1f));
    glTexCoord2f(19.44f, 15.1f);
    glVertex3f(33848.0f, 12061.55f, 41127.0f + (128.0f * 15.1f));
    glTexCoord2f(19.44f, 0.0f);
    glVertex3f(33848.0f, 12061.55f, 41127.0f);
    glEnd();
    glEndList();
    // Chanc Side Beams Bottom (between phys sci and library)
    glNewList(298, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(36108.0f, 10937.68f, 41226.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(36108.0f, 10937.68f, 41226.0f + 32.0f);
    glTexCoord2f(19.44f, 1.0f);
    glVertex3f(33848.0f, 11979.55f, 41226.0f + 32.0f);
    glTexCoord2f(19.44f, 0.0f);
    glVertex3f(33848.0f, 11979.55f, 41226.0f);
    glEnd();
    glEndList();
    // Chanc Side Beams Side (between phys sci and library)
    glNewList(299, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(36108.0f, 10937.68f, 41226.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(36108.0f, 10937.68f + 82.0f, 41226.0f);
    glTexCoord2f(19.44f, 1.0f);
    glVertex3f(33848.0f, 11979.55f + 82.0f, 41226.0f);
    glTexCoord2f(19.44f, 0.0f);
    glVertex3f(33848.0f, 11979.55f, 41226.0f);
    glEnd();
    glEndList();
    // Library Side Planks
    glNewList(257, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4541.0f, 11366.0f, 43056.0f - 1942.0f);
    glTexCoord2f(213.45f, 0.0f);
    glVertex3f(4541.0f + (128.0f * 213.45f), 11366.0f, 43056.0f - 1942.0f);
    glTexCoord2f(228.6f, 16.15f);
    glVertex3f(4541.0f + (128.0f * 213.45f) + 1940.0f, 12080.0f, 43056.0f);
    glTexCoord2f(-15.1f, 16.15f);
    glVertex3f(2608.0f, 12080.0f, 43056.0f);
    glEnd();
    glEndList();
    // Library Side Beams Bottom
    glNewList(296, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4541.0f, 11283.0f, 41114.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4573.0f, 11283.0f, 41114.0f);
    glTexCoord2f(16.15f, 1.0f);
    glVertex3f(4573.0f, 11997.0f, 43056.0f);
    glTexCoord2f(16.15f, 0.0f);
    glVertex3f(4541.0f, 11997.0f, 43056.0f);
    glEnd();
    glEndList();
    // Library Side Beams
    glNewList(297, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(4541.0f, 11283.0f, 41114.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(4541.0f, 11365.0f, 41114.0f);
    glTexCoord2f(16.15f, 1.0f);
    glVertex3f(4541.0f, 12079.0f, 43056.0f);
    glTexCoord2f(16.15f, 0.0f);
    glVertex3f(4541.0f, 11997.0f, 43056.0f);
    glEnd();
    glEndList();

    // spacer between phys sci
    tp.CreateDisplayList(YZ, 97, 32.0f, 128.0f, 33808.0f, 12048.0f, 25344.0f,
                         1.0f, 123.3f);
    // spacer between phys sci amd chanc blocks
    tp.CreateDisplayList(YZ, 98, 32.0f, 128.0f, 35748.0f, 11334.0f, 22096.0f,
                         1.0f, 25.38f);
    // spacer above main posts (chanc side)
    tp.CreateDisplayList(YZ, 99, 32.0f, 128.0f, 31868.0f, 11334.0f, 8100.0f,
                         1.0f, 257.9f);
    // spacer above library
    tp.CreateDisplayList(XY, 202, 128.0f, 32.0f, 4541.0f, 12048.0f, 43056.0f,
                         230.0f, 1.0f);
    // spacer above main posts (library side)
    tp.CreateDisplayList(XY, 203, 128.0f, 32.0f, 4541.0f, 11332.0f, 41114.0f,
                         213.5f, 1.08f);
    // spacer above chanc
    tp.CreateDisplayList(YZ, 204, 128.0f, 128.0f, 33808.0f, 11999.0f, 8100.0f,
                         0.64f, 109.35f);
    tp.CreateYtoZWindowList(205, 33848.0f, 11954.0f, 144.0f, 22096.0f, 3248.0f,
                            0.64f, 25.375f);
    // centre beam between chanc and phys sci
    tp.CreateDisplayList(XZ, 426, 64.0f, 128.0f, 33848.0f, 11954.0f, 22096.0f,
                         1.0f, 25.375f);
    // top corner spacer
    tp.CreateDisplayList(XY, 427, 64.0f, 128.0f, 33808.0f, 11999.0f, 22096.0f,
                         0.75f, 0.75f);

    // Joins where roof slants
    DrawAngledRoofBeam(1, 33848.0f - 1867.0f, 12012.72f - 687.13f, 41226.0, 15.21f);
    DrawAngledRoofBeam(2, 33848.0f - 1481.0f, 12012.72f - 545.07f, 41612.0, 12.0f);
    DrawAngledRoofBeam(3, 33848.0f - 1095.0f, 12012.72f - 403.01f, 41998.0, 8.78f);
    DrawAngledRoofBeam(4, 33848.0f - 709.0f, 12012.72f - 260.94f, 42384.0, 5.57f);
    DrawAngledRoofBeam(5, 33848.0f - 323.0f, 12012.72f - 118.88f, 42770.0, 2.36f);
    DrawAngledRoofBeam2(170, 31980.0f, 11998.0f - 672.41f, 43056.0f - 1827.0f,
                        15.21f);
    DrawAngledRoofBeam2(171, 32366.0f, 11998.0f - 530.35f, 43056.0f - 1441.0f,
                        12.0f);
    DrawAngledRoofBeam2(172, 32752.0f, 11998.0f - 388.28f, 43056.0f - 1055.0f,
                        8.78f);
    DrawAngledRoofBeam2(173, 33138.0f, 11998.0f - 246.22f, 43056.0f - 669.0f, 5.57f);
    DrawAngledRoofBeam2(174, 33524.0f, 11998.0f - 104.16f, 43056.0f - 283.0f, 2.36f);
}

// --------------------------------------------------------------------------------------
//  Creates Angled Roof Beams
// --------------------------------------------------------------------------------------
void DrawAngledRoofBeam(GLuint listNo, GLfloat x, GLfloat y, GLfloat z,
                        GLfloat beamSize) {
    glNewList(listNo, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, z + 32.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y, z);
    glTexCoord2f(beamSize, 1.0f);
    glVertex3f(33848.0f, 12012.72f, z);
    glTexCoord2f(beamSize, 0.0f);
    glVertex3f(33848.0f, 12012.72f, z + 32.0f);
    glEnd();
    glEndList();
    glNewList(listNo + 5, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, z);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(x, y + 82.0f, z);
    glTexCoord2f(beamSize, 1.0f);
    glVertex3f(33848.0f, 12012.72f + 82.0f, z);
    glTexCoord2f(beamSize, 0.0f);
    glVertex3f(33848.0f, 12012.72f, z);
    glEnd();
    glEndList();
}

void DrawAngledRoofBeam2(GLuint listNo, GLfloat x, GLfloat y, GLfloat z,
                         GLfloat beamSize) {
    glNewList(listNo, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x + 32.0f, y, z);
    glTexCoord2f(1.0f, beamSize);
    glVertex3f(x + 32.0f, 11998.0f, 43056.0f);
    glTexCoord2f(0.0f, beamSize);
    glVertex3f(x, 11998.0f, 43056.0f);
    glEnd();
    glEndList();
    glNewList(listNo + 5, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(x, y, z);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(x, y + 82.0f, z);
    glTexCoord2f(1.0f, beamSize);
    glVertex3f(x, 11998.0f + 82.0f, 43056.0f);
    glTexCoord2f(0.0f, beamSize);
    glVertex3f(x, 11998.0f, 43056.0f);
    glEnd();
    glEndList();
}

//--------------------------------------------------------------------------------------
// Display Steps
//--------------------------------------------------------------------------------------
void DisplayEntranceSteps() {
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_PAVING_1));
    for (GLuint i = 258; i < 274; i++)
        glCallList(i);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_EDGE));
    for (GLuint i = 274; i < 290; i++)
        glCallList(i);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_PAVING_1));
    for (GLuint i = 290; i < 293; i++)
        glCallList(i);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_EDGE));
    for (GLuint i = 293; i < 296; i++)
        glCallList(i);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEPS_LIBRARY));
    step  = 0.0f;
    step2 = -51.0f;
    for (GLuint i = 0; i < 10; i++) {
        glPushMatrix();
        glTranslatef(step, step2, 0.0f);
        glCallList(206);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(step, step2, 965.0f);
        glCallList(206);
        glPopMatrix();
        step += 128.0f;
        step2 += -51.0f;
    }
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEPS_LIBRARY_TOP));
    glCallList(207);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 965.0f);
    glCallList(207);
    glPopMatrix();
}

void DrawEntranceSteps() {
    step       = 10000.0f;
    stepLength = 9808.0f;
    for (GLuint i = 258; i < 274; i++) {
        tp.CreateDisplayList(XZ, i, 1024.0f, 512.0f, 31582.0f, step, stepLength,
                             2.2f, 0.277f);
        tp.CreateDisplayList(XY, i + 16, 64.0f, 64.0f, 31582.0f, step - 64.0f,
                             stepLength, 35.0f, 1.0f);
        step -= 48.0f;
        stepLength -= 142.0f;
        if ((i + 3) % 4 == 0) {
            stepLength -= 500.0f;
            step -= 48.0f;
        }
    }
    step       = 9808.0f;
    stepLength = 8882.0f;
    for (GLuint i = 290; i < 293; i++) {
        tp.CreateDisplayList(XZ, i, 1024.0f, 512.0f, 31582.0f, step, stepLength,
                             2.2f, 1.0f);
        tp.CreateDisplayList(XY, i + 3, 64.0f, 64.0f, 31582.0f, step - 64.0f,
                             stepLength, 35.0f, 1.0f);
        step -= 239.0f;
        stepLength -= 1068.0f;
    }

    // steps next to GCL1
    tp.CreateDisplayList(XZ, 206, 128.0f, 1024.0f, 34508.0f, 10000.0f, 41127.0f,
                         1.0f, 0.942f);
    tp.CreateDisplayList(XZ, 207, 256.0f, 1024.0f, 34352.0f, 10000.0f, 41127.0f,
                         0.609f, 0.942f);
}

//--------------------------------------------------------------------------------------
// Display Bench
//--------------------------------------------------------------------------------------
void DisplayBench() {
    step2 = 3860.0f;
    for (int j = 0; j < 11; j++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step2);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_TOP));
        glCallList(400);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE));
        glCallList(401);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 480.0f);
        glCallList(401);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE_2));
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 50.0f);
        glCallList(402);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 430.0f);
        glCallList(402);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_TOP));
        step = 0.0f;
        for (int i = 0; i < 2; i++) {
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, step);
            glCallList(403);
            glPushMatrix();
            glTranslatef(192.0f, 0.0f, 0.0f);
            glCallList(403);
            glPopMatrix();
            glPopMatrix();
            step += 430.0f;
        }
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_SIDE));
        step = 0.0f;
        for (int i = 0; i < 2; i++) {
            glPushMatrix();
            glTranslatef(step, 0.0f, 0.0f);
            glCallList(404);
            glPopMatrix();
            step += 192.0f;
        }

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE));
        glCallList(405);
        glPushMatrix();
        glTranslatef(192.0f, 0.0f, 0.0f);
        glCallList(405);
        glPopMatrix();
        glCallList(406);
        glPushMatrix();
        glTranslatef(192.0f, 0.0f, 0.0f);
        glCallList(406);
        glPopMatrix();

        glPopMatrix();
        step2 += 1930.0f;
        if (j == 4)
            step2 += 5790.0f;
    }

    step2            = 1940.0f;
    GLfloat vertStep = 0.0f;
    for (int j = 0; j < 8; j++) {
        glPushMatrix();
        glTranslatef(step2, 0.0f, vertStep);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_TOP));
        glCallList(407);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE));
        glCallList(408);
        glPushMatrix();
        glTranslatef(480.0f, 0.0f, 0.0f);
        glCallList(408);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_SIDE_2));
        glPushMatrix();
        glTranslatef(50.0f, 0.0f, 0.0f);
        glCallList(409);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(430.0f, 0.0f, 0.0f);
        glCallList(409);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_TOP_2));
        step = 0.0f;
        for (int i = 0; i < 2; i++) {
            glPushMatrix();
            glTranslatef(step, 0.0f, 0.0f);
            glCallList(410);
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 192.0f);
            glCallList(410);
            glPopMatrix();
            glPopMatrix();
            step += 430.0f;
        }
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_3));
        step = 0.0f;
        for (int i = 0; i < 2; i++) {
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, step);
            glCallList(411);
            glPopMatrix();
            step += 192.0f;
        }

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(BENCH_EDGE_2));
        glCallList(412);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 192.0f);
        glCallList(412);
        glPopMatrix();
        glCallList(413);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 192.0f);
        glCallList(413);
        glPopMatrix();

        glPopMatrix();
        step2 += 1940.0f;
        if (j == 1)
            step2 += 1940.0f;
        if (j == 5)
            step2 += 9700.0f;
        if (j == 6) {
            vertStep += 1848.0f;
            step2 = 5926.0f;
        }
    }
}

void DrawBench() {
    tp.CreateDisplayList(XZ, 400, 64.0f, 64.0f, 31760.0f, 10147.0f, 10894.0f,
                         3.0f, 7.5f);
    tp.CreateDisplayList(XY, 401, 64.0f, 64.0f, 31760.0f, 10000.0f, 10894.0f,
                         3.0f, 2.3f);
    tp.CreateDisplayList(XY, 402, 64.0f, 64.0f, 31760.0f, 10000.0f, 10894.0f,
                         3.0f, 1.72f);
    tp.CreateDisplayList(YZ, 403, 64.0f, 64.0f, 31760.0f, 10000.0f, 10894.0f,
                         1.72f, 0.78f);
    tp.CreateDisplayList(YZ, 404, 64.0f, 64.0f, 31760.0f, 10107.0f, 10944.0f,
                         0.625f, 5.938f);
    tp.CreateDisplayList(YZ, 405, 64.0f, 64.0f, 31760.0f, 10107.0f, 10894.0f,
                         0.625f, 0.78f);
    tp.CreateDisplayList(YZ_FLIP, 406, 64.0f, 64.0f, 31760.0f, 10107.0f,
                         11324.0f, 0.625f, 0.78f);

    tp.CreateDisplayList(XZ, 407, 64.0f, 64.0f, 5410.0f, 10147.0f, 41008.0f,
                         7.5f, 3.0f);
    tp.CreateDisplayList(YZ, 408, 64.0f, 64.0f, 5410.0f, 10000.0f, 41008.0f,
                         2.3f, 3.0f);
    tp.CreateDisplayList(YZ, 409, 64.0f, 64.0f, 5410.0f, 10000.0f, 41008.0f,
                         1.72f, 3.0f);
    tp.CreateDisplayList(XY, 410, 64.0f, 64.0f, 5410.0f, 10000.0f, 41008.0f,
                         0.78f, 1.72f);
    tp.CreateDisplayList(XY, 411, 64.0f, 64.0f, 5460.0f, 10107.0f, 41008.0f,
                         5.938f, 0.625f);
    tp.CreateDisplayList(XY, 412, 64.0f, 64.0f, 5410.0f, 10107.0f, 41008.0f,
                         0.78f, 0.625f);
    tp.CreateDisplayList(XY_FLIP, 413, 64.0f, 64.0f, 5410.0f + 430.0f, 10107.0f,
                         41008.0f, 0.78f, 0.625f);
}

//--------------------------------------------------------------------------------------
// Display Extras (signs etc)
//--------------------------------------------------------------------------------------
void DisplayExtras() {
    // Rusty Man like Sculpture
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(RUSTY_MAN));
    glCallList(300);

    // Directions sign next to Sta Travel Shop
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_1));
    glCallList(301);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_1_SIDE_1));
    glCallList(302);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_1_SIDE_2));
    glCallList(303);

    // GCL1 Sign
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_2));
    glCallList(304);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SIGN_2_SIDE));
    glCallList(305);
    glPushMatrix();
    glTranslatef(384.0f, 0.0f, 0.0f);
    glCallList(305);
    glPopMatrix();

    // KBLT
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_EDGE));
    glCallList(306);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_EDGE_2));
    glCallList(307);
    glCallList(308);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_EDGE_CORNER));
    glCallList(309);
    glPushMatrix();
    glTranslatef(2471.0f, 0.0f, 0.0f);
    glCallList(309);
    glPopMatrix();

    // Nexus Sign
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(NEXUS_SIDE));
    glCallList(310);
    glPushMatrix();
    glTranslatef(1280.0f, 0.0f, 0.0f);
    glCallList(310);
    glPopMatrix();

    // Glass Notice Board next to KBLT
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_B_SIDE));
    glCallList(311);
    glPushMatrix();
    glTranslatef(896.0f, 0.0f, 0.0f);
    glCallList(311);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(3904.0f, 0.0f, 0.0f);
    glCallList(311);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(4800.0f, 0.0f, 0.0f);
    glCallList(311);
    glPopMatrix();
    glCallList(435);
    glPushMatrix();
    glTranslatef(768.0f, 0.0f, 0.0f);
    glCallList(435);
    glPopMatrix();

    // Security Sign on Chanc Doorway
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SECURITY_SIGN));
    glCallList(312);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SECURITY_SIGN_2));
    glCallList(313);

    //  Prospective Student Sign
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PSC_SIGN));
    glCallList(314);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(PSC_SIGN_2));
    glCallList(315);

    // Staf Sign
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CO_SIGN));
    glCallList(316);

    // DRINKS MACINE
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_SIDE_2));
    for (GLuint i = 317; i < 319; i++)
        glCallList(i);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_SIDE));
    glPushMatrix();
    glTranslatef(-1152.0f, 0.0f, 0.0f);
    glCallList(317);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_TOP));
    glCallList(319);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRINKS_EDGE));
    glCallList(320);
    glPushMatrix();
    glTranslatef(-1136.0f, 0.0f, 0.0f);
    glCallList(320);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MACHINE_SIDES));
    for (GLuint i = 321; i < 323; i++)
        glCallList(i);
    glCallList(320);
    glPushMatrix();
    glTranslatef(317.12f, 0.0f, 0.0f);
    glCallList(321);
    glPopMatrix();
    glCallList(320);
    glPushMatrix();
    glTranslatef(255.0f, 0.0f, 0.0f);
    glCallList(322);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(MACHINE_SIDES_2));
    glCallList(323);
    glPushMatrix();
    glTranslatef(350.0f, 0.0f, 0.0f);
    glCallList(323);
    glPopMatrix();

    // Doorway Carpet
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CARPET));
    glCallList(324);
    glCallList(429);

    // No Smoking Sign
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(NO_SMOKE_SIGN));
    glCallList(326);
    glCallList(327);

    // Star Travel Sign
    step            = 0.0f;
    GLuint sign     = STA_TRAVEL;
    GLuint signBack = STA_TRAVEL_2;
    GLuint signEdge = STA_TRAVEL_EDGE;
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(sign));
        glCallList(328);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(signEdge));
        glCallList(329);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STA_TRAVEL_BRACKET));
        glCallList(330);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 64.0f);
        glCallList(330);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(signBack));
        glCallList(331);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STA_TRAVEL_BOTTOM));
        glCallList(332);
        glPopMatrix();
        step -= 3840.0f;
        sign     = GS_SIGN;
        signBack = GS_SIGN_2;
        signEdge = GS_SIGN_EDGE;
    }

    // Telephone Boxes
    step = 0.0f;
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_BACK));
        glCallList(333);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FRONT));
        glCallList(334);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_SIDE_1));
        glCallList(335);
        glPushMatrix();
        glTranslatef(285.0f, 0.0f, 0.0f);
        glCallList(335);
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FRONT_2));
        glCallList(336);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_MAIN_SIDE));
        glCallList(337);
        glPushMatrix();
        glTranslatef(285.0f, 0.0f, 0.0f);
        glCallList(337);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_TOP_1));
        glCallList(338);
        glCallList(340);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_SIDE_2));
        glCallList(339);
        glPushMatrix();
        glTranslatef(285.0f, 0.0f, 0.0f);
        glCallList(339);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_TOP_2));
        glCallList(341);
        glCallList(342);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_BOTTOM));
        glCallList(343);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FILL));
        glCallList(348);
        glCallList(349);
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, 168.2f);
        glCallList(349);
        glPopMatrix();
        glCallList(388);
        glPushMatrix();
        glTranslatef(275.2f, 0.0f, 0.0f);
        glCallList(388);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TELEPHONE_FRONT_3));
        glCallList(395);
        glPushMatrix();
        glTranslatef(269.0f, 0.0f, 0.0f);
        glCallList(395);
        glPopMatrix();

        glPopMatrix();
        step += 384.0f;
    }

    // Sides of KBLT
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_1));
    glCallList(345);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_2));
    glCallList(346);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_1));
    glPushMatrix();
    glTranslatef(-2496.0f, 0.0f, 0.0f);
    glCallList(345);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT_SIDE_2));
    glPushMatrix();
    glTranslatef(-2316.0f, 0.0f, 0.0f);
    glCallList(346);
    glPopMatrix();

    // Toilet Signs
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TOILET_WOMEN));
    glCallList(347);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TOILET_MEN));
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1920.0f);
    glCallList(347);
    glPopMatrix();

    // Ledge of Ticket Ofice
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_LEDGE));
    glCallList(419);
    glPushMatrix();
    glTranslatef(0.0f, 32.0f, 0.0f);
    glCallList(419);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_LEDGE_EDGE));
    glCallList(420);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TICKET_LEDGE_EDGE_2));
    glCallList(421);
    glPushMatrix();
    glTranslatef(1208.0f, 0.0f, 0.0f);
    glCallList(421);
    glPopMatrix();
}

void DrawExtras() {
    tp.CreateDisplayList(YZ, 300, 256.0f, 1024.0f, 33808.0f, 10576.0f, 25472.0f,
                         1.0f,
                         1.0f); // Rusty Man

    tp.CreateDisplayList(YZ, 301, 512.0f, 256.0f, 33792.0f, 10320.0f, 40794.0f,
                         0.75f,
                         0.609f); // Sign 1 (end of phys sci)
    tp.CreateDisplayList(XY, 302, 16.0f, 512.0f, 33792.0f, 10320.0f, 40794.0f, 1.0f,
                         0.75f); // side of sign 1
    tp.CreateDisplayList(XY, 303, 16.0f, 512.0f, 33792.0f, 10320.0f, 40950.0f, 1.0f,
                         0.75f); // side of sign 1
    tp.CreateDisplayList(XY, 304, 512.0f, 512.0f, 33637.0f, 10410.0f, 43040.0f,
                         0.75f,
                         0.574f); // Sign 2 (GCL1)

    tp.CreateDisplayList(YZ, 305, 512.0f, 16.0f, 33637.0f, 10410.0f, 43040.0f,
                         0.574f,
                         1.0f); // side of sign 2

    tp.CreateDisplayList(XY, 306, 16.0f, 32.0f, 25633.0f, 10902.0f, 42756.0f,
                         152.88f,
                         1.0f); // KBLT edge top
    tp.CreateDisplayList(XY, 307, 32.0f, 16.0f, 25608.0f, 10000.0f, 42756.0f, 1.0f,
                         56.375f); // KBLT edge left
    tp.CreateDisplayList(XY_FLIP, 308, 32.0f, 16.0f, 28072.0f, 10000.0f,
                         42756.0f, 1.0f, 56.375f); // KBLT right
    tp.CreateDisplayList(XY, 309, 1.0f, 1.0f, 25608.0f, 10902.0f, 42756.0f, 25.0f,
                         32.0f); // KBLT corner
    tp.CreateDisplayList(YZ, 310, 2.0f, 16.0f, 29512.0f, 10288.0f, 43040.0f, 240.0f,
                         1.0f); // Side of Nexus

    tp.CreateDisplayList(YZ, 311, 2.0f, 16.0f, 24456.0f, 10320.0f, 43040.0f, 224.0f,
                         1.0f); // Side of Glassboards
    tp.CreateDisplayList(YZ, 435, 2.0f, 16.0f, 7304.0f, 10256.0f, 43040.0f, 192.0f,
                         1.0f); // Side of Glassboards

    tp.CreateDisplayList(XY, 312, 128.0f, 128.0f, 33752.0f, 10659.0f, 10511.0f,
                         0.75f,
                         0.75f); // security sign
    tp.CreateDisplayList(XY, 313, 128.0f, 128.0f, 33752.0f, 10659.0f, 10513.0f,
                         0.75f,
                         0.75f); // security sign

    tp.CreateDisplayList(XY, 314, 256.0f, 128.0f, 33660.0f, 10836.0f, 20111.0f,
                         0.578f, 0.561f); // PSC sign
    tp.CreateDisplayList(XY, 315, 256.0f, 128.0f, 33660.0f, 10836.0f, 20113.0f,
                         0.578f, 0.561f); // PSC sign

    tp.CreateDisplayList(YZ, 316, 256.0f, 128.0f, 33808.0f, 10256.0f, 34126.0f, 1.0f,
                         1.0f); // CO sign

    tp.CreateDisplayList(YZ, 317, 64.0f, 64.0f, 35856.0f, 10000.0f, 24996.0f, 11.5f,
                         5.47f); // Drinks Machine
    tp.CreateDisplayList(XY, 319, 64.0f, 64.0f, 34704.0f, 10672.0f, 24996.0f, 18.0f,
                         1.0f); // Drinks Machine
    tp.CreateDisplayList(XZ, 318, 64.0f, 64.0f, 34704.0f, 10736.0f, 24996.0f, 18.0f,
                         5.5f); // Drinks Machine
    tp.CreateDisplayList(XY, 320, 16.0f, 2.0f, 35840.0f, 10000.0f, 24996.0f, 1.0f,
                         336.0f); // Drinks Machine
    tp.CreateDisplayList(YZ, 321, 1.0f, 1.0f, 35458.0f, 10000.0f, 25016.0f, 660.0f,
                         300.0f); // Drinks Machine Sides
    tp.CreateDisplayList(YZ, 322, 1.0f, 1.0f, 35163.0f, 10000.0f, 25016.0f, 586.2f,
                         300.0f); // Drinks Machine Sides
    tp.CreateDisplayList(YZ, 323, 1.0f, 1.0f, 34778.0f, 10000.0f, 25016.0f, 593.22f,
                         300.0f); // Drinks Machine Sides

    tp.CreateDisplayList(XZ, 324, 32.0f, 32.0f, 34064.0f, 10000.0f, 26704.0f, 6.0f,
                         20.0f); // Carpet 1st doorway
    tp.CreateDisplayList(XZ, 429, 32.0f, 32.0f, 34064.0f, 10000.0f, 36643.2f, 9.0f,
                         17.4f); // Carpet 2nd doorway

    tp.CreateDisplayList(YZ, 326, 256.0f, 128.0f, 34260.0f, 10320.0f, 36511.0f, 1.1f,
                         1.0f); // No smoke sign doorway 2
    tp.CreateDisplayList(YZ, 327, 256.0f, 128.0f, 34256.0f, 10320.0f, 27303.0f, 1.1f,
                         1.1f); // No smoke sign doorway 1

    tp.CreateDisplayList(XY, 328, 256.0f, 256.0f, 33595.0f, 10828.0f, 40071.0f,
                         0.773f, 0.855f); // Sta Travel sign
    tp.CreateDisplayList(YZ, 329, 256.0f, 64.0f, 33595.0f, 10828.0f, 40071.0f,
                         0.855f,
                         1.0f); // Sta Travel sign edge
    tp.CreateDisplayList(XY, 330, 16.0f, 2.0f, 33792.0f, 10854.0f, 40071.0f, 1.0f,
                         76.0f); // Sta Travel sign bracket
    tp.CreateDisplayList(XY, 331, 256.0f, 256.0f, 33595.0f, 10828.0f, 40135.0f,
                         0.773f, 0.855f); // Sta Travel sign 2
    tp.CreateDisplayList(XZ, 332, 2.0f, 64.0f, 33595.0f, 10828.0f, 40071.0f, 99.0f,
                         1.0f); // Sta Travel bottom

    tp.CreateDisplayList(XY, 333, 512.0f, 512.0f, 33808.0f, 10192.0f, 25344.0f,
                         0.752f, 1.05f); // Telephone Back
    tp.CreateDisplayList(XY, 334, 512.0f, 32.0f, 33882.0f, 10598.0f, 25173.0f,
                         0.557f,
                         0.719f); // Telephone front
    tp.CreateDisplayList(YZ, 335, 32.0f, 256.0f, 33882.0f, 10598.0f, 25173.0f,
                         0.719f,
                         0.7f); // Telephone side top
    tp.CreateDisplayList(XY, 336, 512.0f, 16.0f, 33882.0f, 10621.0f, 25173.0f,
                         0.557f,
                         0.75f); // Telephone front
    tp.CreateDisplayList(YZ, 339, 16.0f, 256.0f, 33882.0f, 10621.0f, 25173.0f, 0.75f,
                         0.7f); // Telephone side
    tp.CreateDisplayList(XZ, 343, 512.0f, 128.0f, 33882.0f, 10268.0f, 25250.0f,
                         0.558f, 0.75f); // Telephone bottom
    tp.CreateDisplayList(XZ, 348, 2.0f, 2.0f, 33918.0f, 10697.84f, 25201.6f, 107.0f,
                         56.9f); // telephone roof
    tp.CreateDisplayList(XZ, 349, 2.0f, 2.0f, 33882.0f, 10633.0f, 25173.0f, 142.6f,
                         2.5f); // telephone roof
    tp.CreateDisplayList(XZ, 388, 2.0f, 2.0f, 33882.0f, 10633.0f, 25173.0f, 5.0f,
                         89.6f); // telephone roof

    tp.CreateDisplayList(YZ, 345, 2.0f, 128.0f, 28104.0f, 10000.0f, 42756.0f, 467.0f,
                         1.0f); // KBLT side
    tp.CreateDisplayList(YZ, 346, 2.0f, 2.0f, 28014.0f, 10000.0f, 42866.0f, 416.0f,
                         98.0f); // KBLT side

    // TELEPHONE ROOF
    tp.CreateAngledPolygon(337, 512.0f, 256.0f, 33882.0f, 33882.0f, 33882.0f,
                           33882.0f, 10268.0f, 10268.0f, 10598.24f, 10598.24f,
                           25250.0f, 25345.34f, 25345.34f, 25173.0f, 6, 4);
    glNewList(338, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(33890.0f, 10633.0f, 25178.0f);
    glTexCoord2f(0.527f, 0.0f);
    glVertex3f(34160.0f, 10633.0f, 25178.0f);
    glTexCoord2f(0.473f, 0.54f);
    glVertex3f(34132.0f, 10697.84f, 25201.6f);
    glTexCoord2f(0.055f, 0.54f);
    glVertex3f(33918.0f, 10697.84f, 25201.6f);
    glEnd();
    glEndList();
    glNewList(341, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(33891.0f, 10633.0f, 25178.0f);
    glTexCoord2f(0.0f, 0.637f);
    glVertex3f(33891.0f, 10633.0f, 25341.0f);
    glTexCoord2f(0.54f, 0.538f);
    glVertex3f(33918.5f, 10697.84f, 25315.6f);
    glTexCoord2f(0.54f, 0.1f);
    glVertex3f(33918.5f, 10697.84f, 25201.6f);
    glEnd();
    glEndList();
    glNewList(342, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(34159.5f, 10633.0f, 25178.0f);
    glTexCoord2f(0.0f, 0.637f);
    glVertex3f(34159.5f, 10633.0f, 25341.0f);
    glTexCoord2f(0.54f, 0.538f);
    glVertex3f(34132.0f, 10697.84f, 25315.6f);
    glTexCoord2f(0.54f, 0.1f);
    glVertex3f(34132.0f, 10697.84f, 25201.6f);
    glEnd();
    glEndList();
    glNewList(340, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(33890.0f, 10631.0f, 25341.0f);
    glTexCoord2f(0.527f, 0.0f);
    glVertex3f(34160.0f, 10631.0f, 25341.0f);
    glTexCoord2f(0.473f, 0.535f);
    glVertex3f(34132.0f, 10697.84f, 25315.4f);
    glTexCoord2f(0.055f, 0.535f);
    glVertex3f(33918.0f, 10697.84f, 25315.4f);
    glEnd();
    glEndList();
    glNewList(395, GL_COMPILE);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(33882.0f, 10268.0f, 25250.0f);
    glTexCoord2f(1.0, 0.0);
    glVertex3f(33898.0f, 10268.0f, 25250.0f);
    glTexCoord2f(1.0f, 0.729f);
    glVertex3f(33898.0f, 10598.24f, 25173.0f);
    glTexCoord2f(0.0f, 0.729f);
    glVertex3f(33882.0f, 10598.24f, 25173.0f);
    glEnd();
    glEndList();

    tp.CreateDisplayList(YZ, 347, 128.0f, 128.0f, 33808.0f, 10384.0f, 28519.0f, 1.0f,
                         1.0f); // toilets sign

    tp.CreateDisplayList(XZ, 419, 2.0f, 128.0f, 22928.0f, 10870.0f, 42960.0f, 604.0f,
                         0.78f); // ticket box ledge
    tp.CreateDisplayList(XY, 420, 2.0f, 32.0f, 22928.0f, 10870.0f, 42960.0f, 604.0f,
                         1.0f); // ticket box ledge edge
    tp.CreateDisplayList(YZ, 421, 32.0f, 2.0f, 22928.0f, 10870.0f, 42960.0f, 1.0f,
                         49.0f); // ticket box ledge edge side
}

// --------------------------------------------------------------------------------------
// Display larger textures such as windows and doors
// --------------------------------------------------------------------------------------

void DisplayLargerTextures() {
    // Gap betweem chanc and phys sci
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_1));
    glCallList(350);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_1B));
    glCallList(351);

    // Chanc Windows Downstairrs
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2));
    step = 1920.0f;
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(352);
        glPopMatrix();
        step += 2880.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2B));
    step = 2880.0f;
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(352);
        glPopMatrix();
        step += 2880.0f;
        if (i == 2)
            step -= 960.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2C));
    step = 6720.0f;
    for (int i = 1; i < 3; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(352);
        glPopMatrix();
        step += 2880.0f;
        if (i == 1)
            step += 1920.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2D));
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3840.0f);
    glCallList(352);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 10560.0f);
    glCallList(352);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2E));
    glCallList(352);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 7680.0f);
    glCallList(352);
    glPopMatrix();

    // Chanc Windows Upstairs
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2US));
    glPushMatrix();
    glTranslatef(0.0f, 1023.0f, 0.0f);
    glCallList(352);
    glPopMatrix();
    step = 9600.0f;
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 1023.0f, step);
        glCallList(352);
        glPopMatrix();
        step += 960.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_2USB));
    step = 960;
    for (int i = 0; i < 9; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 1023.0f, step);
        glCallList(352);
        glPopMatrix();
        step += 960.0f;
    }

    // Physical Science upstairs
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_3));
    step = 3840.0f;
    for (int i = 4; i < 14; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(353);
        glPopMatrix();
        step += 960.0f;
    }
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_3B));
    step = 0.0f;
    for (int i = 0; i < 6; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(353);
        glPopMatrix();
        step += 960.0f;
        if (i == 4)
            step = 13440.0f;
    } //--------------------------------------------------------------

    // toilets
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_4));
    step = 0.0f;
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, step);
        glCallList(354);
        glPopMatrix();
        step += 1920.0f;
    }
    // See draw function for details of below
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_5));
    glCallList(355);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_6));
    glCallList(356);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_7));
    glCallList(357);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_8));
    glCallList(358);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_9));
    glCallList(359);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_10));
    glCallList(360);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_11));
    glCallList(361);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_12));
    glCallList(362);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(NEXUS_SIGN));
    glCallList(363);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_BOARD));
    glCallList(364);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_BOARD_2));
    glCallList(365);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GLASS_BOARD_3));
    glCallList(366);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(KBLT));
    glCallList(367);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENTRANCE));
    glCallList(368);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ENTRANCE_2));
    glCallList(369);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COKE_MACHINE));
    glCallList(370);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COFFEE_MACHINE));
    glCallList(371);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(SWEET_MACHINE));
    glCallList(372);

    // Phys sci door 1
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_13));
    glCallList(373);
    // Phys sci toilets
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_14));
    glCallList(374);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_14B));
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1920.0f);
    glCallList(374);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_15));
    glCallList(375);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_16));
    glCallList(379);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_17));
    glCallList(380);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(EXIT_EAST));
    glCallList(381);

    // Chanc Doorways
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CHANC_DOOR_1));
    glCallList(382);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CHANC_DOOR_2));
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 8640.0f);
    glCallList(382);
    glPopMatrix();

    // Library windows downstairs
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1A));
    glCallList(383);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1));
    step = 1088.0f;
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);
        glCallList(383);
        glPopMatrix();
        step += 3264.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1B));
    step = 2176.0f;
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);
        glCallList(383);
        glPopMatrix();
        step += 3264.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_1C));
    step = 3264.0f;
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);
        glCallList(383);
        glPopMatrix();
        step += 3264.0f;
    }

    // library windows upstairs
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_US_B));
    step = 2176.0f;
    for (int i = 0; i < 9; i++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);
        glCallList(384);
        glPopMatrix();
        step += 1088.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_US_A));
    step = 0.0f;
    glCallList(384);
    glPushMatrix();
    glTranslatef(1088.0f, 0.0f, 0.0f);
    glCallList(384);
    glPopMatrix();

    step = 11968.0f;
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);
        glCallList(384);
        glPopMatrix();
        step += 1088.0f;
    }

    // library doorways
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_DOOR_1));
    glCallList(385);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_DOOR_2));
    glCallList(386);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOW_LIB_LONG));
    glCallList(387);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WINDOWPOST_LIB_FRONT));
    glCallList(389);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DOOR_POST_LIB));
    glCallList(414);
    glPushMatrix();
    glTranslatef(77.0f, 0.0f, 0.0f);
    glCallList(414);
    glPopMatrix();

    // top of toilet door
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(TOILET_DOOR_TOP));
    glCallList(422);
    glCallList(423);

    // West Exit
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(EXIT_WEST));
    glCallList(450);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(ABOVE_WINDOW_BLOCK_CHANC));
    glCallList(451);
    // window next to steps
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(STEP_WINDOW));
    glCallList(452);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(CARPET));
    glCallList(453);
}

void DrawLargerTextures() {
    // CHANC
    // Gap between chanc and phy sci y1142 z3248
    tp.CreateYtoZWindowList(350, 35879.0f, 10000.0f, 1147.0f, 22096.0f, 1540.0f,
                            0.714f,
                            0.95f); // w190.63  245
    tp.CreateYtoZWindowList(351, 35879.0f, 10000.0f, 1147.0f, 23740.0f, 1605.0f,
                            0.714f,
                            0.98f); // w183
    // chanc windows
    tp.CreateYtoZWindowList(352, 33895.0f, 10256.0f, 576.0f, 9599.0f, 867.0f, 0.664f,
                            1.0f); // w170
    // chanc doors
    tp.CreateYtoZWindowList(382, 33895.0f, 10000.0f, 832.0f, 10559.0f, 867.0f, 0.96f,
                            1.0f); // w246

    // PHYS SCI
    // phys sci upstairs
    tp.CreateYtoZWindowList(353, 33895.0f, 11411.0f, 445.0f, 26702.0f, 883.0f,
                            0.504f,
                            1.0f); // 129x256
    // phys sci toilets
    tp.CreateYtoZWindowList(354, 33895.0f, 10576.0f, 255.0f, 27662.0f, 883.0f,
                            0.578f,
                            1.0f); // 73.93x256
    // phys sci toilets 3rd
    tp.CreateYtoZWindowList(355, 33895.0f, 10576.0f, 255.0f, 33422.0f, 919.0f, 0.57f,
                            1.0f); // 71.04x256
    // serving window
    tp.CreateYtoZWindowList(356, 33895.0f, 10320.0f, 511.0f, 34419.0f, 845.0f,
                            0.605f,
                            1.0f); // 155x256
    // last window
    tp.CreateYtoZWindowList(357, 33895.0f, 10320.0f, 511.0f, 38239.0f, 320.0f, 1.0f,
                            0.626f); // 256x160.3
    // first purple post window
    tp.CreateYtoZWindowList(358, 33895.0f, 10000.0f, 832.0f, 31519.0f, 865.0f, 0.96f,
                            1.0f); // 246.2x256
    // second purple post window
    tp.CreateYtoZWindowList(359, 33895.0f, 10000.0f, 832.0f, 32461.0f, 883.0f, 0.94f,
                            1.0f); // 241.2x256
    // third purple post window
    tp.CreateYtoZWindowList(360, 33895.0f, 10000.0f, 832.0f, 35341.0f, 867.0f, 0.96f,
                            1.0f); // 246.2x256
    // first red window
    tp.CreateYtoZWindowList(361, 33865.0f, 10000.0f, 832.0f, 39216.0f, 839.0f,
                            0.992f,
                            1.0f); // 254.5x256
    // second red window
    tp.CreateYtoZWindowList(362, 33865.0f, 10000.0f, 832.0f, 40151.0f, 448.0f, 1.0f,
                            0.54f); // 256x138

    tp.CreateXtoYWindowList(363, 43040.0f, 29512.0f, 1280.0f, 10288.0f, 480.0f, 1.0f,
                            0.745f); // NEXUS
    tp.CreateXtoYWindowList(364, 43040.0f, 28360.0f, 896.0f, 10320.0f, 448.0f, 1.0f,
                            1.0f); // Glassboard 1
    tp.CreateXtoYWindowList(365, 43040.0f, 24456.0f, 896.0f, 10320.0f, 448.0f, 1.0f,
                            1.0f); // Glassboard 2
    tp.CreateXtoYWindowList(366, 43040.0f, 7304.0f, 768.0f, 10256.0f, 384.0f, 1.0f,
                            1.0f); // Glassboard 2
    tp.CreateXtoYWindowList(367, 42756.0f, 25640.0f, 2432.0f, 10000.0f, 902.0f, 1.0f,
                            0.742f); // KBLT

    tp.CreateYtoZWindowList(368, 33840.0f, 9086.0f, 2200.0f, 4688.0f, 1100.0f,
                            1.0f, 1.0f);
    tp.CreateXtoYWindowList(369, 4688.0f, 31632.0f, 2208.0f, 9086.0f, 2208.0f,
                            1.0f, 1.0f);

    tp.CreateXtoYWindowList(370, 25016.0, 35458.0, 317.12f, 10000.0f, 660.0f, 0.96f,
                            1.0f); // Coke Machine
    tp.CreateXtoYWindowList(371, 25016.0f, 35163.0f, 255.0f, 10000.0f, 586.2f,
                            0.867f,
                            1.0f); // Coffee Machine
    tp.CreateXtoYWindowList(372, 25016.0f, 34778.0f, 350.0f, 10000.0f, 593.22f,
                            0.59f, 1.0f); // Sweet Machine
    // phys sci door 1
    tp.CreateYtoZWindowList(373, 34320.0f, 10000.0f, 832.0f, 26752.0f, 552.0f,
                            1.0f, 0.66f); // 256x169.85
    // phys sci toilets
    tp.CreateYtoZWindowList(374, 33872.0f, 10000.0f, 768.0f, 28646.0f, 322.0f,
                            1.0f, 0.833f); // 256x106.67 toilet doors
    // phys sci door 2
    tp.CreateYtoZWindowList(375, 34342.0f, 10000.0f, 832.0f, 36639.0f, 1216.0f,
                            0.68f, 1.0f); // 256x175.16

    tp.CreateXtoYWindowList(379, 43152.0f, 33232.0f, 384.0f, 10000.0f, 768.0f, 1.0f,
                            1.0f); // GCL1 doorway
    tp.CreateXtoYWindowList(380, 43152.0f, 32720.0f, 384.0f, 10000.0f, 768.0f, 1.0f,
                            1.0f); // GCL1 doorway

    tp.CreateYtoZWindowList(381, 36047.0f, 9422.0f, 1410.0f, 41127.0f, 1929.0f,
                            0.725f, 1.0f); // Exit East  375x512

    tp.CreateXtoYWindowList(383, 43152.0f, 11055.0f, 1014.0f, 10388.0f, 380.0f, 1.0f,
                            0.75f); // 256x96 Library Window downstairs
    tp.CreateXtoYWindowList(384, 43152.0f, 8879.0f, 1014.0f, 11412.0f, 444.0f, 1.0f,
                            0.876f); // 256x112 Library Window upstairs
    tp.CreateXtoYWindowList(385, 43120.0f, 8189.0f, 614.0f, 10000.0f, 768.0f, 0.78f,
                            1.0f); // library door 1
    tp.CreateXtoYWindowList(386, 43152.0f, 8880.0f, 2072.0f, 9998.0f, 770.0f, 1.0f,
                            0.742f); // 256x136 library door 2
    tp.CreateXtoYWindowList(387, 43152.0f, 23023.0f, 1014.0f, 10305.0f, 464.0f, 1.0f,
                            0.914f); // silver long library window
    tp.CreateXtoYWindowList(389, 43096.0f, 8803.0f, 77.0f, 9998.0f, 775.0f, 0.6f,
                            1.0f); // library post
    tp.CreateYtoZWindowList(414, 8803.0f, 9998.0f, 775.0f, 43096.0f, 77.0f, 1.0f,
                            0.5625f); // library post
    tp.CreateYtoZWindowList(422, 33872.0f, 10768.0f, 64.0f, 28646.0f, 856.0f,
                            1.0f, 1.0f); // top of toilet door female
    tp.CreateYtoZWindowList(423, 33872.0f, 10768.0f, 64.0f, 30566.0f, 840.0f,
                            1.0f, 1.0f); // top of toilet door male
    tp.CreateYtoZWindowList(450, 2352.0f, 10000.0f, 896.0f, 41168.0f, 1792.0f,
                            1.0f, 1.0f); // west exit
    tp.CreateDisplayList(XZ, 451, 400.0f, 256.0f, 2352.0f, 10896.0f, 41168.0f,
                         0.64f, 7.0f); // above west exit
    tp.CreateXtoYWindowList(452, 41127.0, 35280.0f, 320.0f, 10128.0f, 704.0f, 0.91f,
                            1.0f); // w 233 window by steps (end of phys sci)
    tp.CreateDisplayList(XZ, 453, 2.0f, 2.0f, 35856.0f, 9400.0f, 40500.0f, 180.0f,
                         1380.0f); // block at bottom of steps
}

// --------------------------------------------------------------------------------------
// Display grass and slopes
// --------------------------------------------------------------------------------------

void DisplayGrass() {
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRASS));
    glCallList(79);
    glCallList(111);
    glCallList(460);
    glCallList(477);
    for (GLuint i = 461; i < 477; i++)
        glCallList(i);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRASS_2));
    glCallList(198);

    // USED IF REQUIRED DARKER HILL
    // glBindTexture(GL_TEXTURE_2D, tp.GetTexture(GRASS_HILL));
    // for (int i = 461; i < 477; i++) glCallList(i);
}

void DrawGrass() {
    tp.CreateDisplayList(XZ, 79, 64.0f, 64.0f, 4848.0f, 9086.0f, 3408.0f,
                         417.5f, 45.0f);
    tp.CreateDisplayList(XZ, 111, 64.0f, 64.0f, 4848.0f, 10000.0f, 10000.0f,
                         417.5f, 481.5f);

    // Slope ate the entrance
    tp.CreateAngledPolygon(198, 64.0f, 64.0f, 4848.0f, 31568.0f, 31568.0f,
                           4848.0f, 9086.0f, 9086.0f, 10000.0f, 10000.0f,
                           6200.0f, 6200.0f, 10000.0f, 10000.0f, 1, 1);
    // Lower hill in the centre
    tp.CreateDisplayList(XZ, 460, 64.0f, 64.0f, 9000.0f, 10200.0f, 19000.0f,
                         203.125f, 281.25f);
    tp.CreateAngledPolygon(461, 64.0f, 64.0f, 9000.0f, 22000.0f, 22000.0f,
                           9000.0f, 10000.0f, 10000.0f, 10200.0f, 10200.0f,
                           17000.0f, 17000.0f, 19000.0f, 19000.0f, 1, 1);

    tp.CreateAngledPolygon(462, 64.0f, 64.0f, 9000.0f, 22000.0f, 22000.0f,
                           9000.0f, 10200.0f, 10200.0f, 10000.0f, 10000.0f,
                           37000.0f, 37000.0f, 40000.0f, 40000.0f, 1, 1);

    tp.CreateAngledPolygon(463, 64.0f, 64.0f, 22000.0f, 27000.0f, 27000.0f,
                           22000.0f, 10200.0f, 10000.0f, 10000.0f, 10200.0f,
                           19000.0f, 19000.0f, 37000.0f, 37000.0f, 1, 1);

    tp.CreateAngledPolygon(464, 64.0f, 64.0f, 6500.0f, 9000.0f, 9000.0f,
                           6500.0f, 10000.0f, 10200.0f, 10200.0f, 10000.0f,
                           19000.0f, 19000.0f, 37000.0f, 37000.0f, 1, 1);

    tp.CreateAngledPolygon(465, 64.0f, 64.0f, 9000.0f, 9000.0f, 9000.0f,
                           6500.0f, 10000.0f, 10000.0f, 10200.0f, 10000.0f,
                           17000.0f, 17000.0f, 19000.0f, 19000.0f, 4, 1);

    tp.CreateAngledPolygon(466, 64.0f, 64.0f, 22000.0f, 22000.0f, 27000.0f,
                           22000.0f, 10000.0f, 10000.0f, 10000.0f, 10200.0f,
                           17000.0f, 17000.0f, 19000.0f, 19000.0f, 1, 1);

    tp.CreateAngledPolygon(467, 64.0f, 64.0f, 22000.0f, 27000.0f, 22000.0f,
                           22000.0f, 10200.0f, 10000.0f, 10000.0f, 10000.0f,
                           37000.0f, 37000.0f, 40000.0f, 40000.0f, 4, 1);

    tp.CreateAngledPolygon(468, 64.0f, 64.0f, 6500.0f, 9000.0f, 9000.0f,
                           9000.0f, 10000.0f, 10200.0f, 10000.0f, 10000.0f,
                           37000.0f, 37000.0f, 40000.0f, 40000.0f, 1, 1);

    // higher hilltop
    tp.CreateDisplayList(XZ, 477, 64.0f, 64.0f, 14000.0f, 10425.0f, 28000.0f,
                         62.5f, 78.125f);

    tp.CreateAngledPolygon(469, 64.0f, 64.0f, 14000.0f, 18000.0f, 18000.0f,
                           14000.0f, 10200.0f, 10200.0f, 10425.0f, 10425.0f,
                           23000.0f, 23000.0f, 28000.0f, 28000.0f, 1, 1);

    tp.CreateAngledPolygon(470, 64.0f, 64.0f, 14000.0f, 18000.0f, 18000.0f,
                           14000.0f, 10425.0f, 10425.0f, 10200.0f, 10200.0f,
                           33000.0f, 33000.0f, 36000.0f, 36000.0f, 1, 1);

    tp.CreateAngledPolygon(471, 64.0f, 64.0f, 10000.0f, 14000.0f, 14000.0f,
                           10000.0f, 10200.0f, 10425.0f, 10425.0f, 10200.0f,
                           28000.0f, 28000.0f, 33000.0f, 33000.0f, 1, 1);

    tp.CreateAngledPolygon(472, 64.0f, 64.0f, 18000.0f, 22000.0f, 22000.0f,
                           18000.0f, 10425.0f, 10200.0f, 10200.0f, 10425.0f,
                           28000.0f, 28000.0f, 33000.0f, 33000.0f, 1, 1);

    tp.CreateAngledPolygon(473, 64.0f, 64.0f, 14000.0f, 14000.0f, 14000.0f,
                           10000.0f, 10200.0f, 10200.0f, 10425.0f, 10200.0f,
                           23000.0f, 23000.0f, 28000.0f, 28000.0f, 4, 1);

    tp.CreateAngledPolygon(474, 64.0f, 64.0f, 18000.0f, 18000.0f, 22000.0f,
                           18000.0f, 10200.0f, 10200.0f, 10200.0f, 10425.0f,
                           23000.0f, 23000.0f, 28000.0f, 28000.0f, 1, 1);

    tp.CreateAngledPolygon(475, 64.0f, 64.0f, 18000.0f, 22000.0f, 18000.0f,
                           18000.0f, 10425.0f, 10200.0f, 10200.0f, 10200.0f,
                           33000.0f, 33000.0f, 36000.0f, 36000.0f, 1, 1);

    tp.CreateAngledPolygon(476, 64.0f, 64.0f, 10000.0f, 14000.0f, 14000.0f,
                           14000.0f, 10200.0f, 10425.0f, 10200.0f, 10200.0f,
                           33000.0f, 33000.0f, 36000.0f, 36000.0f, 1, 1);
}

// --------------------------------------------------------------------------------------
// Display Light Fittings
// --------------------------------------------------------------------------------------
void DisplayLights() {
    // Light Fitting
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(LIGHT));
    GLfloat beamstep = 0.0f;
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(32905.0f, 11200.0f, 11134.0f + beamstep);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
        glCallList(376);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(32905.0f, 11265.0f, 11134.0f + beamstep);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
        glCallList(376);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(32905.0f, 11330.0f, 11134.0f + beamstep);
        glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
        glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
        glCallList(376);
        glPopMatrix();
        beamstep += 8492.0f;
    }

    // Light Supports
    beamstep = 0.0f;
    for (int i = 0; i < 4; i++) {
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(LIGHT_SUPPORT_2));
        step = -40.0f;
        for (int k = 0; k < 2; k++) {
            for (int j = 0; j < 2; j++) {
                glPushMatrix();
                glTranslatef(step, 0.0f, 0.0f + beamstep);
                glCallList(377);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(step, 0.0f, -40.0f + beamstep);
                glCallList(377);
                glPopMatrix();
                step += 8.0f;
            }
            step += 64.0f;
        }

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(LIGHT_SUPPORT));
        step = -40.0f;
        for (int k = 0; k < 2; k++) {
            step2 = 0.0f;
            for (int j = 0; j < 2; j++) {
                glPushMatrix();
                glTranslatef(step, 0.0f, 0.0f + step2 + beamstep);
                glCallList(378);
                glPopMatrix();
                glPushMatrix();
                glTranslatef(step, 0.0f, -40.0f + step2 + beamstep);
                glCallList(378);
                glPopMatrix();
                step2 += 8.0f;
            }
            step += 80.0f;
        }
        beamstep += 8492.0f;
    }
}

void DrawLights() {
    // Fittings
    glNewList(376, GL_COMPILE);
    glBegin(GL_QUADS);
    gluQuadricDrawStyle(glu_cylinder, GLU_LINE);
    gluCylinder(glu_cylinder, 75.0, 75.0, 60.0, 15, 100);
    glEnd();
    glEndList();

    tp.CreateDisplayList(YZ, 377, 2.0f, 8.0f, 32900.0f, 11330.0f, 11150.0f, 220.0f,
                         1.0f); // supports
    tp.CreateDisplayList(XY, 378, 8.0f, 2.0f, 32900.0f, 11330.0f, 11150.0f, 1.0f,
                         220.0f); // supports
}

// --------------------------------------------------------------------------------------
// Display drainpipe and tuckshop serving counter
// --------------------------------------------------------------------------------------

void DisplayCylinders() {
    // drainpipe
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(DRAINPIPE));
    glPushMatrix();
    glTranslatef(24200.0f, 9850.0f, 43090.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
    glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
    glScalef(1.0, 1.0f, 1125.0f);
    glCallList(437);
    glPopMatrix();

    // serving counter
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_TOP));
    glCallList(439);
    glPushMatrix();
    glTranslatef(33800.0f, 10340.0f, 34848.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
    glCallList(441);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_SIDE));
    glCallList(438);
    glTranslatef(0.0f, 0.0f, 10.0f);
    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_TOP));
    glCallList(441);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(COUNTER_SIDE));
    glCallList(440);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 276.0f);
    glCallList(440);
    glPopMatrix();
}

void DrawCylinders() {
    // Drainpipe
    glNewList(437, GL_COMPILE);
    glBegin(GL_QUADS);
    gluQuadricDrawStyle(glu_cylinder, GLU_FILL);
    gluCylinder(glu_cylinder, 10.0, 10.0, 2.0, 15, 15);
    glEnd();
    glEndList();

    // Serving Counter
    glNewList(438, GL_COMPILE);
    glBegin(GL_QUADS);
    gluQuadricDrawStyle(glu_cylinder, GLU_FILL);
    gluCylinder(glu_cylinder, 138.0, 138.0, 16.0, 20, 50);
    glEnd();
    glEndList();
    glNewList(441, GL_COMPILE);
    glBegin(GL_QUADS);
    gluQuadricDrawStyle(glu_cylinder, GLU_FILL);
    gluDisk(glu_cylinder, 0.0, 138.0, 20, 50);
    glEnd();
    glEndList();

    tp.CreateDisplayList(XZ, 439, 1.0f, 1.0f, 33800.0f, 10340.0f, 34710.0f,
                         120.0f, 276.0f);
    tp.CreateDisplayList(XY, 440, 4.0f, 16.0f, 33800.0f, 10324.0f, 34710.0f,
                         30.0f, 1.0f);
}

// --------------------------------------------------------------------------------------
// Display Wall by Entrance
// --------------------------------------------------------------------------------------
void DisplayStepBricks() {
    step = 0.0f;

    for (int j = 0; j < 2; j++) {
        glPushMatrix();
        glTranslatef(step, 0.0f, 0.0f);
        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS));
        for (GLuint i = 478; i < 487; i++)
            glCallList(i);

        glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_TOP));
        for (GLuint i = 488; i < 493; i++)
            glCallList(i);

        glPushMatrix();
        glTranslatef(31572.0f, 9222.0f, 6126.0f);
        glRotatef(-18.69f, 1.0f, 0.0f, 0.0f);
        glTranslatef(-31572.0f, -9222.0f, -6126.0f);
        glCallList(493);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(31572.0f, 9461.0f, 7213.0f);
        glRotatef(-20.31f, 1.0f, 0.0f, 0.0f);
        glTranslatef(-31572.0f, -9462.0f, -7213.0f);
        glCallList(494);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(31572.0f, 9722.0f, 8302.0f);
        glRotatef(-17.35f, 1.0f, 0.0f, 0.0f);
        glTranslatef(-31572.0f, -9722.0f, -8302.0f);
        glCallList(495);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(31572.0f, 9939.0f, 9332.4f);
        glRotatef(-19.83f, 1.0f, 0.0f, 0.0f);
        glTranslatef(-31572.0f, -9942.0f, -9332.4f);
        glCallList(496);
        glPopMatrix();
        glPopMatrix();
        step += -64.0f;
    }

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_COVER));
    for (GLuint i = 497; i < 502; i++)
        glCallList(i);
    glPushMatrix();
    glTranslatef(31572.0f, 9222.0f, 6126.0f);
    glRotatef(-18.69f, 1.0f, 0.0f, 0.0f);
    glTranslatef(-31572.0f, -9222.0f, -6126.0f);
    glCallList(502);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(31572.0f, 9462.0f, 7213.0f);
    glRotatef(-20.21f, 1.0f, 0.0f, 0.0f);
    glTranslatef(-31572.0f, -9462.0f, -7213.0f);
    glCallList(503);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(31572.0f, 9722.0f, 8302.0f);
    glRotatef(-17.35f, 1.0f, 0.0f, 0.0f);
    glTranslatef(-31572.0f, -9722.0f, -8302.0f);
    glCallList(504);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(31572.0f, 9939.0f, 9332.4f);
    glRotatef(-19.83f, 1.0f, 0.0f, 0.0f);
    glTranslatef(-31572.0f, -9942.0f, -9332.4f);
    glCallList(505);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_EDGE));
    glCallList(506);

    glBindTexture(GL_TEXTURE_2D, tp.GetTexture(WALL_BRICK_STEPS_EDGE_2));
    glCallList(507);
}
void DrawStepBricks() {
    tp.CreateDisplayList(YZ, 478, 128.0f, 128.0f, 31582.0f, 9914.0f, 9872.0f,
                         1.7188f, 1.75f);
    tp.CreateDisplayList(YZ, 488, 32.0f, 128.0f, 31582.0f, 10134.0f, 9868.0f,
                         1.0f, 1.78f);

    tp.CreateDisplayList(YZ, 479, 128.0f, 128.0f, 31582.0f, 9530.0f, 9006.0f,
                         3.21875f, 6.0f);
    tp.CreateDisplayList(YZ, 489, 32.0f, 128.0f, 31582.0f, 9942.0f, 9004.0f,
                         1.0f, 2.55f);

    tp.CreateDisplayList(YZ, 480, 128.0f, 128.0f, 31582.0f, 9350.0f, 7918.0f,
                         2.90625f, 6.0f);
    tp.CreateDisplayList(YZ, 490, 32.0f, 128.0f, 31582.0f, 9722.0f, 7916.0f,
                         1.0f, 3.0f);

    tp.CreateDisplayList(YZ, 481, 128.0f, 128.0f, 31582.0f, 9158.0f, 6830.0f,
                         2.375f, 6.0f);
    tp.CreateDisplayList(YZ, 491, 32.0f, 128.0f, 31582.0f, 9462.0f, 6830.0f,
                         1.0f, 2.99f);

    tp.CreateDisplayList(YZ, 482, 128.0f, 128.0f, 31582.0f, 8966.0f, 4590.0f,
                         2.0f, 15.0f);
    tp.CreateDisplayList(YZ, 492, 32.0f, 128.0f, 31582.0f, 9222.0f, 4590.0f,
                         1.0f, 12.0f);

    tp.CreateAngledPolygon(483, 128.0f, 128.0f, 31582.0f, 31582.0f, 31582.0f,
                           31582.0f, 9094.0f, 9094.0f, 9462.0f, 9094.0f,
                           5742.0f, 6830.0f, 6830.0f, 5742.0f, 5, 1);
    tp.CreateDisplayList(YZ, 493, 32.0f, 128.0f, 31582.0f, 9222.0f, 6126.0f,
                         1.0f, 5.92f);

    tp.CreateAngledPolygon(484, 128.0f, 128.0f, 31582.0f, 31582.0f, 31582.0f,
                           31582.0f, 9414.0f, 9414.0f, 9722.0f, 9414.0f,
                           7086.0f, 7918.0f, 7918.0f, 7086.0f, 5, 1);
    tp.CreateDisplayList(YZ, 494, 32.0f, 128.0f, 31582.0f, 9462.0f, 7213.0f,
                         1.0f, 5.93f);

    tp.CreateAngledPolygon(485, 128.0f, 128.0f, 31582.0f, 31582.0f, 31582.0f,
                           31582.0f, 9594.0f, 9594.0f, 9942.0f, 9722.0f,
                           8302.0f, 9006.0f, 9006.0f, 8302.0f, 5, 1);
    tp.CreateDisplayList(YZ, 495, 32.0f, 128.0f, 31582.0f, 9722.0f, 8302.0f,
                         1.0f, 5.82f);

    tp.CreateAngledPolygon(486, 128.0f, 128.0f, 31582.0f, 31582.0f, 31582.0f,
                           31582.0f, 9914.0f, 9914.0f, 10134.0f, 9914.0f,
                           9262.0f, 9872.0f, 9872.0f, 9262.0f, 5, 1);
    tp.CreateDisplayList(YZ, 496, 32.0f, 128.0f, 31582.0f, 9942.0f, 9332.4f,
                         1.0f, 4.545f);

    tp.CreateDisplayList(XZ, 497, 64.0f, 128.0f, 31518.0f, 10166.0f, 9868.0f,
                         1.0f, 1.78f);
    tp.CreateDisplayList(XZ, 498, 64.0f, 128.0f, 31518.0f, 9974.0f, 9004.0f,
                         1.0f, 2.55f);
    tp.CreateDisplayList(XZ, 499, 64.0f, 128.0f, 31518.0f, 9754.0f, 7916.0f,
                         1.0f, 3.0f);
    tp.CreateDisplayList(XZ, 500, 64.0f, 128.0f, 31518.0f, 9494.0f, 6830.0f,
                         1.0f, 2.99f);
    tp.CreateDisplayList(XZ, 501, 64.0f, 128.0f, 31518.0f, 9254.0f, 4590.0f,
                         1.0f, 12.0f);
    tp.CreateDisplayList(XZ, 502, 64.0f, 128.0f, 31518.0f, 9254.0f, 6126.0f,
                         1.0f, 5.92f);
    tp.CreateDisplayList(XZ, 503, 64.0f, 128.0f, 31518.0f, 9494.0f, 7213.0f,
                         1.0f, 5.95f);
    tp.CreateDisplayList(XZ, 504, 64.0f, 128.0f, 31518.0f, 9754.0f, 8302.0f,
                         1.0f, 5.82f);
    tp.CreateDisplayList(XZ, 505, 64.0f, 128.0f, 31518.0f, 9974.0f, 9332.4f,
                         1.0f, 4.545f);
    tp.CreateDisplayList(XY, 506, 64.0f, 32.0f, 31518.0f, 10134.0f, 10095.84f,
                         1.0f, 1.0f);
    tp.CreateDisplayList(XY, 507, 64.0f, 64.0f, 31518.0f, 9914.0f, 10095.84f,
                         1.0f, 3.4376f);
}

//--------------------------------------------------------------------------------------
//  Map and Welcome screens
//--------------------------------------------------------------------------------------
void DrawMapExit() {
    tp.CreateDisplayList(0, 448, 256.0f, 256.0f, 10.0f, 10.0f, 0.0f, 0.855f,
                         1.0f); // map
    tp.CreateDisplayList(0, 449, 512.0f, 512.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                         1.0f); // welcome screen
    tp.CreateDisplayList(0, 454, 256.0f, 64.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                         1.0f); // welcome screen
}

//--------------------------------------------------------------------------------------
//  Create display lists
//	Numbers indicate list numbers
//--------------------------------------------------------------------------------------
void CreateTextureList() {
    DrawGrass();            // 79, 111, 198, 460-477
    DrawChancPosts();       // 11-15, 235-237
    DrawDoorPosts();        // 25-27, 199
    DrawAboveWindowBlock(); // 20-24, 39, 43-46, 49-50, 53-56, 64-72, 95-96 208-213, 223-234, 238-239, 415, 424-425
    DrawPurplePosts();      // 29-32
    DrawRedPosts();         // 33-35
    DrawPhysSciPosts();     // 16-17, 36-38, 40-42
    DrawDoorPaving();       // 47-48
    DrawLibraryPosts();     // 57-63, 442-447
    DrawMainPosts();        // 18-19, 51-52
    DrawPavement();         // 28, 73-94, 240-249, 428, 436
    DrawBricks(); // 101-110, 112-169, 180-197, 200-201, 390-399, 430-434
    DrawRoof(); // 1-10, 97-100, 170-179, 202-205, 214-222, 250-257, 296-299, 426-427
    DrawEntranceSteps();  // 258-295, 206-207
    DrawExtras();         // 300-349, 388, 395, 419-421, 429, 435
    DrawLargerTextures(); // 350-375, 379-387, 389, 414-418, 422-423, 450-453
    DrawLights();         // 376-378
    DrawBench();          // 400-413
    DrawStepBricks();     // 478-507
    DrawCylinders();      // 437-441
    DrawMapExit();        // 448-449, 454
                          // 455-459
}

//--------------------------------------------------------------------------------------
//  Increments frame count used for setting movement speed
//--------------------------------------------------------------------------------------
void IncrementFrameCount() {
    float t = (static_cast<GLfloat>((clock() - lastClock))) /
              static_cast<GLfloat>(CLOCKS_PER_SEC);
    frameCount++;

    // reset after t
    if (t > 0.1f) {
        stepIncrement  = t / frameCount * 1400;
        angleIncrement = t / frameCount;
        frameCount     = 0;
        lastClock      = clock();
    }
}
