/*
 
 MIT License (MIT)
 
 Copyright (c) 2013 Clement CN Tsang
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 */


#import <UIKit/UIKit.h>
#import "KITAssetDataSource.h"
#import "KITAssetCollectionDataSource.h"
#import "KITCustomAssetPickerController.h"

@protocol KITAssetsPickerControllerDelegate;

/**
 *  A controller that allows picking multiple photos and videos from user's photo library.
 */
@interface KITAssetsPickerController : UIViewController <KITCustomAssetPickerController>

/**
 *  The assets picker’s delegate object.
 */
@property (nonatomic, weak) id <KITAssetsPickerControllerDelegate> delegate;

@property (nonatomic, weak) NSArray <id <KITAssetCollectionDataSource>> *collectionDataSources;

/**
 *  The selected assets.
 *
 *  It contains selected asset objects. The order of the objects is the selection order.
 *  
 *  You can use this property to select assets initially when presenting the picker.
 */
@property (nonatomic, strong) NSMutableArray *selectedAssets;

/**
 *  Determines whether or not the cancel button is visible in the picker.
 *
 *  The cancel button is visible by default. To hide the cancel button, (e.g. presenting the picker in `UIPopoverController`)
 *  set this property’s value to `NO`.
 */
@property (nonatomic, assign) BOOL showsCancelButton;

/**
 *  Determines whether or not the empty albums is shown in the album list.
 *
 *  All albums are visible by default. To hide albums without assets matched with `assetsFetchOptions`,
 *  set this property’s value to `NO`.
 *
 *  @see assetsFetchOptions
 */
@property (nonatomic, assign) BOOL showsEmptyAlbums;

/**
 *  Determines whether or not the number of assets is shown in the album list.
 *
 *  The number of assets is visible by default. To hide the number of assets, (e.g. implementing `shouldShowAsset` delegate method)
 *  set this property’s value to `NO`.
 */
@property (nonatomic, assign) BOOL showsNumberOfAssets;

/**
 *  Determines whether or not the selection order is shown in the grid view.
 *
 *  Only a checkmark is shown on selected assets by default. To shows the order of selection,
 *  set this property’s value to `YES`.
 *
 *  It is also suggested to add border width of the selected grids. Please refer to the demo app on adding border.
 */
@property (nonatomic, assign) BOOL showsSelectionIndex;


/**
 *  @name Managing Selections
 */

/**
 *  Selects an asset in the picker.
 *
 *  @param asset The asset to be selected.
 *
 *  @see deselectAsset:
 */
- (void)selectAsset:(id<KITAssetDataSource> )asset;

/**
 *  Deselects an asset in the picker.
 *
 *  @param asset The asset to be deselected.
 *
 *  @see selectAsset:
 */
- (void)deselectAsset:(id<KITAssetDataSource> )asset;

@end


/**
 *  The `KITAssetsPickerControllerDelegate` protocol defines methods that allow you to to interact with the assets picker interface
 *  and manage the selection and highlighting of assets in the picker.
 *
 *  The methods of this protocol notify your delegate when the user selects, highlights, finish picking assets, or cancels the picker operation.
 *
 *  The delegate methods are responsible for dismissing the picker when the operation completes.
 *  To dismiss the picker, call the `dismissViewControllerAnimated:completion:` method of the presenting controller
 *  responsible for displaying `KITAssetsPickerController` object.
 *
 *  The picked assets are asset objects.
 */
@protocol KITAssetsPickerControllerDelegate <NSObject>


/**
 *  @name Closing the Picker
 */

/**
 *  Tells the delegate that the user finish picking photos or videos.
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param assets An array containing picked asset objects.
 *
 *  @see assetsPickerControllerDidCancel:
 */
- (void)assetsPickerController:(id<KITCustomAssetPickerController>)picker didFinishPickingAssets:(NSArray *)assets;

@optional

/**
 *  Tells the delegate that the user cancelled the pick operation.
 *
 *  @param picker The controller object managing the assets picker interface.
 *
 *  @see assetsPickerController:didFinishPickingAssets:
 */
- (void)assetsPickerControllerDidCancel:(id<KITCustomAssetPickerController>)picker;


/**
 *  @name Configuting Asset Selection View
 */

/**
 *  Ask the delegate the layout of asset selection view (UICollectionView).
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param contentSize  The bounds size of current view.
 *  @param trait The trait collection of current view.
 *
 *  @return Custom `UICollectionViewLayout` for the asset selection view.
 */
- (UICollectionViewLayout *)assetsPickerController:(id<KITCustomAssetPickerController>)picker collectionViewLayoutForContentSize:(CGSize)contentSize traitCollection:(UITraitCollection *)trait;


/**
 *  Ask the delegate if the asset selection view should sroll to bottom on shown.
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param assetCollection  The asset collection of asset selection view.
 *
 *  @return `YES` (the default) if the asset grid should scroll to bottom on shown or `NO` if it should not.
 */
- (BOOL)assetsPickerController:(id<KITCustomAssetPickerController>)picker shouldScrollToBottomForAssetCollection:(id<KITAssetCollectionDataSource>)assetCollection;


/**
 *  @name Enabling Assets
 */

/**
 *  Ask the delegate if the specified asset should be enabled for selection.
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param asset  The asset to be enabled.
 *
 *  @return `YES` if the asset should be enabled or `NO` if it should not.
 *
 *  @see assetsPickerController:shouldShowAsset:
 */
- (BOOL)assetsPickerController:(id<KITCustomAssetPickerController>)picker shouldEnableAsset:(id<KITAssetDataSource> )asset;


/**
 *  @name Managing the Selected Assets
 */

/**
 *  Asks the delegate if the specified asset should be selected.
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param asset  The asset to be selected.
 *
 *  @return `YES` if the asset should be selected or `NO` if it should not.
 *
 *  @see assetsPickerController:shouldDeselectAsset:
 */
- (BOOL)assetsPickerController:(id<KITCustomAssetPickerController>)picker shouldSelectAsset:(id<KITAssetDataSource> )asset;

/**
 *  Tells the delegate that the asset was selected.
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param asset  The asset that was selected.
 *
 *  @see assetsPickerController:didDeselectAsset:
 */
- (void)assetsPickerController:(id<KITCustomAssetPickerController>)picker didSelectAsset:(id<KITAssetDataSource> )asset;

/**
 *  Asks the delegate if the specified asset should be deselected.
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param asset  The asset to be deselected.
 *
 *  @return `YES` if the asset should be deselected or `NO` if it should not.
 *
 *  @see assetsPickerController:shouldSelectAsset:
 */
- (BOOL)assetsPickerController:(id<KITCustomAssetPickerController>)picker shouldDeselectAsset:(id<KITAssetDataSource> )asset;

/**
 *  Tells the delegate that the item at the specified path was deselected.
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param asset  The asset that was deselected.
 *
 *  @see assetsPickerController:didSelectAsset:
 */
- (void)assetsPickerController:(id<KITCustomAssetPickerController>)picker didDeselectAsset:(id<KITAssetDataSource> )asset;



/**
 *  @name Managing Asset Highlighting
 */

/**
 *  Asks the delegate if the specified asset should be highlighted.
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param asset  The asset to be highlighted.
 *
 *  @return `YES` if the asset should be highlighted or `NO` if it should not.
 */
- (BOOL)assetsPickerController:(id<KITAssetsPickerControllerDelegate>)picker shouldHighlightAsset:(id<KITAssetDataSource> )asset;

/**
 *  Tells the delegate that asset was highlighted.
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param asset  The asset that was highlighted.
 *
 *  @see assetsPickerController:didUnhighlightAsset:
 */
- (void)assetsPickerController:(id<KITAssetsPickerControllerDelegate>)picker didHighlightAsset:(id<KITAssetDataSource> )asset;


/**
 *  Tells the delegate that the highlight was removed from the asset.
 *
 *  @param picker The controller object managing the assets picker interface.
 *  @param asset  The asset that had its highlight removed.
 *
 *  @see assetsPickerController:didHighlightAsset:
 */
- (void)assetsPickerController:(id<KITAssetsPickerControllerDelegate>)picker didUnhighlightAsset:(id<KITAssetDataSource> )asset;




/**
 *  @name Notifications
 */

/**
 *  Sent when the assets selected or deselected
 *
 *  The notification’s `object` is an `NSArray` object of selected assets
 */
extern NSString * const KITAssetsPickerSelectedAssetsDidChangeNotification;

/**
 *  Sent when asset is selected
 *
 *  The notification’s `object` is an asset that is selected
 */
extern NSString * const KITAssetsPickerDidSelectAssetNotification;

/**
 *  Sent when asset is deselected
 *
 *  The notification’s `object` is an asset that is deselected
 */
extern NSString * const KITAssetsPickerDidDeselectAssetNotification;


@end