#import <AppKit/AppKit.h>
#import "DrawShapeTypeDelegate.h"
#import "SetAttributeDelegate.h"
#import "ChangeElementAttributeDelegate.h"
#import "OperationInsideShapeDelegate.h"
#import "SetLayerOrderDelegate.h"
#import "DocumentSettingsView.h"


@class Element;
@class StageTextView;
@class GroupingBox;




enum
{
	ALIGN_LEFT			= 0,
	ALIGN_RIGHT,
	ALIGN_VERT,
	ALIGN_TOP,
	ALIGN_BOTTOM,
	ALIGN_HORZ
};
typedef NSInteger		AlignType;



enum
{
	DISTRIBUTION_LEFT	= 0,
	DISTRIBUTION_RIGHT,
	DISTRIBUTION_CENTER
};
typedef NSInteger		DistributionType;



enum
{
	SPACING_HORZ		= 0,
	SPACING_VERT
};
typedef NSInteger		SpacingType;


enum
{
	SHAPE_NORMAL		= 0,
	SHAPE_CUT,
	SHAPE_COPY
};
typedef NSInteger		ShapeCutCopyType;

/*
 StageView is the drawing board on which all elements live.
 It contains drawn shape array and drawing shape object.
 Once user draw the shape, new shape is added in shape array.
 
 @params:	shapeType:			current shape type to draw
 curShape:			current shape object to draw
 shapeArray:			drawn shape array
 isDragingShape:		when the shape is draging, YES. otherwise NO
 isSelectedShape:	when the shape is selected already, YES. otherwise NO
 isSelArea:			when the mouse select the range rect, YES. otherwise NO
 isCutOrCopy:		when the selected shape is cut/copy, YES. otherwise NO
 clipBoardArray:		using by cut/copy/paste of shape. We don't use NSPasteBoard because it is standard system ability.
 attributeDelegate:	delegate to attribute panel
 textboxView:		it shows when the text box shape is editing
 gridLineArray:		grid line array.
 */

@interface StageView : NSView
<DrawShapeTypeDelegate,OperationInsideElementDelegate, ChangeElementAttributeDelegate, NSTextViewDelegate, NSCoding, NSTableViewDataSource, NSTableViewDelegate>

{
	ElementType							elementType;
	Element                             *currentElement;
	NSMutableArray						*elementArray;
    NSMutableArray                      *selElementArray;
	
	NSInteger							nHitTest; // where the mouse last touched down ?
	
	NSPoint								ptStart;
	NSPoint								ptEnd;
	
	BOOL								isDragingShape;
	BOOL								isSelectedShape;
    BOOL								isSelArea;
	
	id<SetAttributeDelegate>			attributeDelegate;
    id<SetLayerOrderDelegate>			layerDelegate;
	
	IBOutlet StageTextView              *textboxView;
    IBOutlet NSScrollView               *sv;
    
    NSFont                              *lastFontSelected;
    
    BOOL isDraggingElement;
    
    int elementCount;
    
    
    int numberOfGroupings;
    IBOutlet NSButton *groupItems;
    IBOutlet NSButton *documentSettingsButton;
    IBOutlet NSPopover *documentSettingsPopover;
    
    IBOutlet NSPanel *panel;

    
    NSMutableArray *groupingBoxes;
    
    NSMutableArray *rows;
    NSMutableArray *rowMargins; // The margin for the nth row. So the first margin in this array is for row(1) and so on
    
    NSMutableArray *leftToRightTopToBottom;
	
	NSMutableArray						*gridLineArray;
	
	NSMutableArray						*clipBoardArray;
	
	ShapeCutCopyType					CutOrCopyFlag;
    
    //document settings
    IBOutlet DocumentSettingsView *documentSettingsView;
    NSRect documentContainer; // change this to an element with a rect in it
    
    //IBOutlet NSPopUpButton *typeFaceName;
    //IBOutlet NSPopUpButton *typeFaceTrait;
    
    //Font panel bits
    IBOutlet NSColorWell *fontColorWell;
    
    //IBOutlet NSTextField                *sizeTextField;
    IBOutlet NSStepper                  *kerningStepper;
    IBOutlet NSTextField                *kerningTextField;
    IBOutlet NSStepper                  *leadingStepper;
    IBOutlet NSTextField                *leadingTextField;
    IBOutlet NSTextField                *fontSizeTextField2;
    
     
    IBOutlet NSSegmentedControl         *fontTraitControl;
    
    //Flags
    BOOL elementBeenDroppedToStage; //Has an element ever touched the stage since the app last opened?
    
    NSMutableString *layoutType;
    
    NSMutableArray *orderOfLayers;


    BOOL								isShowFontTab;
	NSMutableArray						*fontFaceArray;
	IBOutlet NSTableView				*fontTableView;
    
    // background appearance
    BOOL showGridlines;
    IBOutlet NSColorWell *backgroundColorWell;
    
    BOOL abortConversion;
}
@property (nonatomic, strong) NSMutableArray *sortedArray;
@property (nonatomic, strong) NSMutableString *jsCode2;
@property (nonatomic, strong) NSMutableString *pageTitle;
@property (nonatomic, strong) NSMutableArray *finalGrouping;
@property (nonatomic, strong) NSMutableArray *solos;
@property (nonatomic, strong) NSMutableArray *firstAndLastRowsInContainer;
@property (nonatomic, strong) NSMutableDictionary *textStyles;
@property (nonatomic, strong) NSURL *directoryURLToPlaceFiles;
@property (nonatomic, strong) NSString *outputFolderPath;


//background Appearance
@property (nonatomic) BOOL showGridlines;

@property (strong) NSPanel *panel;
//Flags
@property (assign) BOOL elementBeenDroppedToStage;



@property (nonatomic, strong) Element *currentElement;
@property (strong) id<SetAttributeDelegate>		attributeDelegate;
@property (strong) id<SetLayerOrderDelegate>		layerDelegate;
@property (nonatomic, assign) int elementCount;
@property (nonatomic, assign) int numberOfGroupings;
@property (nonatomic, strong) NSButton *groupItems;
@property (nonatomic, strong) NSButton *documentSettingsButton;
@property (nonatomic, strong) NSPopover *documentSettingsPopover;
@property (nonatomic, strong) NSMutableArray *groupingBoxes;
@property (nonatomic, strong) NSMutableArray *rows;
@property (nonatomic, strong) NSMutableArray *rowMargins;
@property (nonatomic, strong) NSMutableArray *leftToRightTopToBottom;

@property (nonatomic, strong) StageTextView *textboxView;
@property (strong, nonatomic) NSScrollView *sv;

@property (nonatomic, strong) NSMutableArray *elementArray;
@property (nonatomic, strong) NSMutableArray *selElementArray;
@property (nonatomic, strong) DocumentSettingsView *documentSettingsView;
@property (nonatomic, assign) NSRect documentContainer;
@property (nonatomic, strong) NSColor *stageBackgroundColor;

//TextBox Menu items

// Labels 
@property (strong) IBOutlet NSTextField *fontFamilyLabel; //
@property (strong) IBOutlet NSTextField *fontStyleLabel; //
@property (strong) IBOutlet NSTextField *textSizeLabel; //
@property (strong) IBOutlet NSTextField *kerningLabel; //
@property (strong) IBOutlet NSTextField *leadingLabel; //
@property (strong) IBOutlet NSTextField *fontcolourWellLabel; //
@property (strong) IBOutlet NSTextField *buttonTextLabel;

// Fields

@property (nonatomic, strong)  IBOutlet NSPopUpButton *typeFaceName;
@property (nonatomic, strong) IBOutlet NSPopUpButton *typeFaceTrait;
@property (strong) IBOutlet NSTextField *fontSizeTextField2;
@property (strong) IBOutlet NSTextField *kerningField;
@property (strong) IBOutlet NSTextField *leadingField; //
@property (strong, nonatomic) NSColorWell *fontColorWell; 
@property (strong, nonatomic) NSSegmentedControl *fontTraitControl;
@property (strong, nonatomic) NSTextField *buttonTextField;
@property (strong, nonatomic) IBOutlet NSTextField *stageBackgroundColorAsHex;


// Stepper
@property (strong, nonatomic) NSStepper *kerningStepper;
@property (strong, nonatomic) NSStepper *leadingStepper;






@property (nonatomic, strong) IBOutlet NSPopover *textPopover;//NSPopover *textPopover;
//@property (strong) NSTextField *sizeTextField;




@property (strong, nonatomic) NSMutableString *layoutType;
@property (strong, nonatomic) NSMutableArray *orderOfLayers;

@property (strong) IBOutlet NSView			*fontView;
@property (strong) IBOutlet NSSearchField	*searchField;
@property (nonatomic) BOOL					isShowFontTab;

@property (nonatomic) BOOL koObservableMapped;
@property (strong, nonatomic) NSString *koObservable;

@property (strong, nonatomic) IBOutlet NSTextField *marginAboveEachRowLabel;
@property (strong, nonatomic) IBOutlet NSTextField *marginAboveEachRow;

@property (strong, nonatomic) NSMutableArray *idsInsideDyRow;

@property (strong, nonatomic) NSMutableString *currentMessage;

@property (strong, nonatomic) NSString *numberOfImages;

@property (assign) float totalNumberOfCycles;

@property (assign) float cycleCount;

//Font based methods
-(IBAction)setFontTrait:(id)sender;
-(IBAction)setFontSize:(id)sender;
-(IBAction)setTypeFaceFamily:(id)sender;
-(IBAction)setTypeStyle:(id)sender;
-(void)setKerningValue:(NSNumber *)kerningValueReceived;
-(void)setLeadingValue:(NSNumber *)leadingValueReceived;
-(IBAction)setAlignmentOfText:(id)sender;
-(void)updateCustomFontMenu:(NSDictionary*)attributes;


-(IBAction)setTopMarginForRow:(id)TextField;


//VALIDATION OF ELEMENTS EDITED
-(BOOL)isElementIDUnique: (NSMutableString *)string;

//GET ELEMENT BY ID
-(Element*)elementWithID: (NSMutableString *)stringID;

//Button
-(IBAction)labelButton:(id)sender;


//Drawing methods
-(IBAction)displayDocumentSettingsView:(id)sender;

-(void) postNotificationForImageToResize;
-(void) postNotificationForImageToHold;

//Rulers
- (void)updateRulers;
- (void)updateHorizontalRuler;
- (void)updateVerticalRuler;
- (void)setRulerOffsets;
- (IBAction)zoomIn:(id)sender;
- (IBAction)zoomOut:(id)sender;

//Popvers
-(IBAction)clearPopover:(id)sender;
-(void)closeSettingsPopover;

//Sort layer panel
- (void)ResortLayer;
- (void)ResortShapes:(NSIndexSet *)from to:(NSInteger)to;


//Moving and positioning of Elements
-(BOOL)updateOverlappingVariable;

/*
 @function:		DeselectAllShaps
 @params:		nothing
 @return:       void
 @purpose:		deselect all Element in shapeArray.
 */
- (void)DeselectAllShaps;


/*
 @function:		DisableEditing
 @params:		nothing
 @return:		void
 @purpose:		disable editing all text boxes
 */
- (void)DisableEditing;


/*
 @function:		SetTextBoxText
 @params:		nothing
 @return:		void
 @purpose:		set the text of textbox to selected text box shape
 */
- (void)SetTextBoxText;


/*
 @function:		MoveSelectedElement
 @params:		offset:			Element's move offset
				hitTest:		Element's hit test
 @return:		void
 @purpose:		move all selected Element in selElementArray
 */
- (void)MoveSelectedElements:(NSSize)offset HitTest:(NSInteger)hitTest;

/*
 @function:		IsContainShape
 @params:		shape1:			source shape object to contain
				shape2:			dest shape object to be contained
				point:			source shape's offset
 @return:		The shape1 contains the shape2, return YES. otherwise NO.
 @purpose:		This function check the shape1 contains the shape that the shape2's position pluse offset.
 */
- (BOOL)IsContainShape:(Element *)shape1 dst:(Element *)shape2 offset:(NSPoint)point;


/*
 @function:		AlignElement
 @params:		flag:			alignment flag: this parameter is one of
								ALIGN_LEFT, ALIGN_RIGHT, ALIGN_VERT, ALIGN_TOP, ALIGN_BOTTOM, ALIGN_HORZ
 @return:		void
 @purpose:		This function called when the user click the align button in alignment panel.
				The purpos is to align of the selected Element by flag.
 */
- (void)AlignElements:(AlignType)flag;


/*
 @function:		DistributionElement
 @params:		flag:			distribution flag: this parameter is one of
								DISTRIBUTION_LEFT, DISTRIBUTION_RIGHT, DISTRIBUTION_CENTER
 @return:		void
 @purpose:		This function called when the user click the distribution button in alignment panel.
				The purpos is to align distribution of the selected Element by flag.
 */
- (void)DistributionElement:(DistributionType)flag;


/*
 @function:		GetDistributionDistance
 @params:		flag:			it is same with the paramenter of DistributionElement
 @return:		distance between Element
 @purpose:		This function returns the distance between the selected Element.
 */
- (CGFloat)GetDistributionDistance:(DistributionType)flag;


/*
 @function:		SpaceEvenlyElement
 @params:		spacing:		distance between the selected Element
				flag:			spacing flag: this paramenter is one of SPACING_VERT, SPACING_HORZ
 @return:		void
 @purpose:		This function called when the user click the spaceing evenly button in alignment panel.
				The purpos is to make the same distance between Element by spacing.
 */
- (void)SpaceEvenlyElement:(NSInteger)spacing flag:(SpacingType)flag;


/*
 @function:		SelectElementByIndex
 @params:		index: index of shape to select
 @return:		void
 @purpose:		This function select the shape by index
 */
- (void)SelectElementByIndex:(NSInteger)index;




- (NSData *)SaveProjectToFile:(NSString*)filename;


/*
 @function:		OpenProjectFromFile
 @params:		data:			file data
 @return:		open sucessfully, return YES. otherwise NO.
 @purpose:		This function read shapes value from filename and create shapes of stageview.
 */
- (BOOL)OpenProjectFromFile:(NSData *)data;


/*
 @function:		IsSelectedShape
 @params:		void
 @return:		if some shape is selected, return YES. otherwise NO
 @purpose:		The purpose is to check some shape are selected.
 */
- (BOOL)IsSelectedShape;


// Cut, copy, paster and delete
- (void)CutSelElements;
- (void)CopySelElements;
- (void)PasteSelElements;
- (void)DeleteAllElements;
- (void)DeleteSelElements;
- (void)DeleteSubElements:(Element*)element;




/*
 @function:		CreateClipBoardRecursive
 @params:		buffer:				shape buffer
 srcShape:		original parent shape
 dstShape:		target parent shape
 @return:		void
 @purpose:		The purpose is to create shape into buffer recursively from selShapeArray again.
 */
- (void)CreateClipBoardRecursive:(NSMutableArray*)buffer src:(Element*)srcShape dst:(Element*)dstShape;


/*
 @function:		CreateAdvancedShape
 @params:		filename:	image file name to create a advanced shape
 rt:			bound rect of the new advanced shape
 @return:       void
 @purpose:		This function create the new advanced image shape from the advanced shape panel.
 */
- (void)CreateImageOnStage:(NSURL*)filePath rtBound:(NSRect)rt;


- (IBAction)InsertImageToStage:(id)sender;

/*
 @function:		ChangeAttribueOfElement
 @params:		offset:		The value to change
 hitTest:	The type of value (Moving: SHT_MOVEAPEX, Resizing: SHT_RESIZE)
 @return:		void
 @purpos:		Set the attribute of shape by changing stepper in AttributePanel.
 */
- (void)ChangeAttribueOfElement:(CGSize)offset HitTest:(NSInteger)hitTest;

- (BOOL)insideMyFrame:(NSPoint)pt;

/*
 @function:		createContainerElement
 @params:		width: width of container shape
 @return:		void
 @purpose:		This function create container shape.
 */
- (void)createContainerElement:(CGFloat)width;
- (void)showFontTab;
- (void)hideFontTab;
- (void)selectFontofCurrentTextBox:(NSString *)fontName;


- (void)InitAttributeBySelected;

- (void)ChangeURLStringOFElement:(NSString *)url;
@end



@interface StageView (flexibileWidth)
-(CGSize)sizeAsPercentageOfHighestContainingElement: (Element*)selElement;
-(CGSize)sizeOfHighestContainingElement: (Element*)selElement;
-(CGSize)updateElementWithPercentagesAndAttributesPanelWithElementAttributes:(Element*)selElement;
-(void)updateSizeInPixelsWhenScrollViewSizeChangess:(Element*)selElement;
@end


@interface StageView (colorsShadowsGradients)
-(void)updateStageViewBackgroundColor: (NSDictionary *)dict;
-(NSString *)hsla:(NSColor *)color;
- (void)drawShapeShadow:(CGFloat)angle Distance:(CGFloat)dist ColorR:(CGFloat)r ColorG:(CGFloat)g ColorB:(CGFloat)b Opacity:(CGFloat)alpha Blur:(CGFloat)blur Direction:(BOOL)d Index:(NSInteger)index;
- (void)addShapeShadow:(CGFloat)angle Distance:(CGFloat)dist ColorR:(CGFloat)r ColorG:(CGFloat)g ColorB:(CGFloat)b Opacity:(CGFloat)alpha Blur:(CGFloat)blur Direction:(BOOL)d;
- (void)removeShapeShadow:(NSInteger)index;
@end


@interface StageView (knockout)
-(NSString*)viewModelFrom:(NSMutableDictionary*)dyRow amongstElements:(NSArray*)sortedArray;
-(NSString*)generateClassFromDynamicRow: (NSMutableDictionary*)dyRowDict withElementsOnStage: (NSArray*)sortedArrayOnStage;
-(NSString*)classStructureOf:(NSMutableDictionary*)dyRow amongstElements:(NSArray*)sortedArray;
-(NSString *)actionCodeString: (Element*)ele;
-(NSString *)dataSourceBindingCode: (Element*)ele;
-(NSString *)visibilityBindingCode: (Element*)ele;
-(NSString*)dataSourceNameContainingKey: (Element*)ele;
@end


@interface StageView (conversion)
-(NSArray*)elementsInside: (NSMutableDictionary *)elementBeingTested usingElements: (NSArray*) sortedArrayOnStage;
BOOL hasLeadingNumberInString(NSString* s);
@end


@interface StageView (backgroundAppearance)
-(IBAction)toggleGridlineVisibility:(id)sender;
-(IBAction)changeStageBackgroundColor:(id)sender;
-(void)hexValueForStageColor;
-(IBAction)updateStageViewBackgroundColorWithHex:(id)sender;
@end


