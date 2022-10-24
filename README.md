# Voice SDK for Unreal Engine
The Voice SDK enables you to bring voice interactions to your app experiences. Use the Voice SDK to enhance the AR/VR experience with more natural and flexible ways for people to interact with the app. For example, voice commands can shortcut controller actions with a single phrase, or interactive conversation can make the app more engaging.

To learn more about the Voice SDK visit the Oculus Developer docs and read through the [Voice SDK Overview](https://developer.oculus.com/documentation/unreal/vsdk-overview/)

## Getting Started
### Installation
There are two ways to install Voice SDK for Unreal Engine. You can download one of the release packages, or you can clone the individual repositories.

#### Release Package Installation
1. Grab the latest release zip from [Releases](https://github.com/wit-ai/voicesdk-unreal/releases/)
2. Extract the zip in your plugins directory.

#### Git Repo Clone
1. Change to your Plugins directory
2. Clone Voice SDK:
```git clone https://github.com/wit-ai/voicesdk-unreal```
3. Clone Wit Unreal: ```git clone https://github.com/wit-ai/wit-unreal```

### Add Voice to GameEngine.ini
Once you have the plugin installed in your plugins directory there's one more step. You need to add a few lines to the Config/DefaultEngine.ini
```
[Voice]
bEnabled=True
```

## Documentation
* [Voice SDK Online Documentation](https://developer.oculus.com/documentation/unreal/vsdk-overview/)
* [Wit.ai Documentation](https://wit.ai/docs)
    * Voice SDK uses Wit.ai to power its speech recognition, text to speech, and natural language functionality. To learn more about Wit.ai check out the Wit.ai Documentation.

## License
The license for `voicesdk-unreal` can be found in [LICENSE](https://github.com/wit-ai/voicesdk-unreal/blob/main/LICENSE) file in the root directory of this source tree.

You can also find the applicable Oculus License here: https://developer.oculus.com/licenses/oculussdk

The MIT license applies to only certain, clearly marked documents. If an individual file does not indicate which license it is subject to, then the Oculus License applies.

## Terms of Use
Our terms of use can be found at https://opensource.facebook.com/legal/terms.

Use of Wit.ai services fall under the terms of use of Wit.ai found here: https://wit.ai/terms.

## Privacy Policy
Our privacy policy can be found at https://opensource.facebook.com/legal/privacy.

The privacy policy for the Wit.ai service can be found at https://wit.ai/privacy.

Please see the Voice SDK Overview for additional applicable terms and policies.

https://developer.oculus.com/documentation/unreal/vsdk-overview/
