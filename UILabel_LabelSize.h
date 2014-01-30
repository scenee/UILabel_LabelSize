//
//  UILabel_LabalSize.h
//
//  Created by Shin Yamamoto on 30/1/2014
//
//

@interface UILabel (LabelSize)
- (CGSize)labelSizeToFitWidth:(CGFloat)width;
- (CGSize)labelSizeToFitHeight:(CGFloat)height;
- (CGSize)labelSizeToFit:(CGSize)size;
- (CGSize)labelSize;
@end

/** NOTE:
 -[UILabel textRectForBounds:limitedToNumberOfLines:]で取得したRectだと
 ヒラギノ角ゴシック体で、gやpのleadingがある文字の下が切れてしまう問題がある。
 そのため、-[NSAttributedString boundingRectWithSize:options:context:]を利用している。
 このとき、optionには、必ず、NSStringDrawingUsesLineFragmentOrigin,NSStringDrawingUsesFontLeadingが必要
 */

@implementation UILabel(LabelSize)

- (CGSize)labelSizeToFitWidth:(CGFloat)width
{
  CGSize maxSize = CGSizeMake(width, CGFLOAT_MAX);
  return [self labelSizeToFit:maxSize];
}

- (CGSize)labelSizeToFitHeight:(CGFloat)height
{
  CGSize maxSize = CGSizeMake(CGFLOAT_MAX, height);
  return [self labelSizeToFit:maxSize];
}

- (CGSize)labelSizeToFit:(CGSize)maxSize
{
  NSStringDrawingOptions options = NSStringDrawingUsesLineFragmentOrigin |  NSStringDrawingUsesFontLeading;
  if (self.lineBreakMode ==  NSLineBreakByTruncatingHead ||
      self.lineBreakMode ==  NSLineBreakByTruncatingTail ||
      self.lineBreakMode ==  NSLineBreakByTruncatingMiddle )
  {
    options |= NSStringDrawingTruncatesLastVisibleLine;
  }
  NSLineBreakMode mode  = self.lineBreakMode;
  self.lineBreakMode = NSLineBreakByWordWrapping;
  
  if (self.numberOfLines > 0) {
    maxSize = CGSizeMake(maxSize.width, self.font.lineHeight * self.numberOfLines);
  }
  
  CGRect textRect  = [self.attributedText boundingRectWithSize:maxSize options:options context:NULL];
  self.lineBreakMode = mode;
  return textRect.size;
}

- (CGSize)labelSize
{
  CGSize maxSize = CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX);
  return [self labelSizeToFit:maxSize];
}

@end
