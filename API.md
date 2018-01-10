#LED ScrollBoard API

## Set Data

### Background
URL: **`/bg`**  
METHOD: **`GET`**
####PARAMS
| Parameter | Description | Values |
| ---       | ---         | ---    |
| `mode` | Set Background Type | Int - [0 = Fill / 1 = Rainbow]
| `wait` | Set Rainbow Speed | Int - 1-30 (higher = slower - default: 23)
| `color` | Set Background Color | String - Hex without '#'
| `brightness` | Set Background Brightness |  Int - 1-30 (higher = brighter - default: 16)

### Text
URL: **`/sc`**  
METHOD: **`GET`**
####PARAMS
| Parameter | Description | Values |
| ---       | ---         | ---    |
| `scrolltext` | Set the Text | String - $X is replaced with the icon number X
| `wait` | Set Text Speed | Int - 1-30 (higher = slower - recommended: 8 <= n <= 25 - default: 20)
| `color` | Set Text Color | String - Hex without '#'
| `brightness` | Set Text Brightness |  Int - 1-30 (higher = brighter - default: 28)

### Icon
URL: **`/ic`**  
METHOD: **`GET`**
####PARAMS
| Parameter | Description | Values |
| ---       | ---         | ---    |
| `icon` | Set the current icon number | Int - 1 <= x <= 10
| `anim` | Animate to next icon | Int - 0 (= yes) / 1 (= no)
| `wait` | Set Icon Animation Speed | Int - (1-30 higher = slower)
| `pixels` | Set Icon Pixels | String - 35 (5*7) concatenated HEX values of the pixels
| `brightness` | Set Icon Brightness |  Int - (1-30 higher = brighter)

  
## Read Data

### Get the Status
URL: **`/js`**  
METHOD: **`GET`**

#### Returns
```javascript
{
  "brightness": "BRIGHTNESS_OF_THE_BOARD",
  "act_icon": "CURRENT_ICON_NUMBER", 
  "bg_brightness": "BACKGROUND_BRIGHTNESS", 
  "scroll_brightness": "TEXT_BRIGHTNESS",
  "icon_brightness": "ICON_BRIGHTNESS"
}
```
