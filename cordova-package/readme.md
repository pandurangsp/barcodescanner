# Add a Plugin for Use in an Oracle Visual Builder Mobile Application

The `cordova-package.zip` that you have just downloaded is an Apache Cordova project. Use the [Cordova CLI](http://cordova.apache.org/docs/en/9.x/reference/cordova-cli/index.html "Cordova cli") to add plugins to this project, build the project for Android or iOS, and upload the APK or IPA file that the build generates to Oracle Visual Builder.

------------
## Before You Begin
1. Ensure [Apache Cordova](http://cordova.apache.org/#getstarted "Cordova") is installed on your computer.  Version 10.0.0 is required.
2. Ensure you install and set up the tools for each mobile platform for which you will build a mobile application.
   - [iOS Requirements](https://cordova.apache.org/docs/en/latest/guide/platforms/ios/index.html#requirements-and-support "iOS Requirements")
   - [Android Requirements](https://cordova.apache.org/docs/en/latest/guide/platforms/android/index.html#installing-the-requirements "Android Requirements")
3. Ensure  you have the platform-specific signing files. 
   - [iOS Signing](https://cordova.apache.org/docs/en/dev/guide/platforms/ios/index.html#signing-an-app "iOS Signing")
   - [Android Signing](https://cordova.apache.org/docs/en/latest/guide/platforms/android/index.html#signing-an-app "Android Signing") 
4. For code signing convenience, create a `build.json` file in the root directory.
   - [iOS build.json](https://cordova.apache.org/docs/en/latest/guide/platforms/ios/#using-buildjson "iOS build.json")
   - [Android build.json](https://cordova.apache.org/docs/en/latest/guide/platforms/android/index.html#using-buildjson "Android build.json")
5. For iOS, ensure you have:
   - Xcode 12.1 or newer installed.
   - iOS SDK 13 or newer installed.
   **NOTE:**  Starting June 30, 2020, Apple will not accept new applications, or updates to existing applications, built with older iOS SDKs.
------------
## How to Add a Plugin for an Oracle Visual Builder Mobile Application
1. To add a mobile platform to the project, run the appropriate command from the root directory where you extracted the `cordova-package.zip` file.

   - `cordova platform add android --nosave`
   - `cordova platform add ios --nosave`

   **IMPORTANT**:  If you build your template for both the iOS and Android platforms, and you plan to use Oracle Cloud as the authentication mechanism, add the Android platform to the project first, then add the iOS platform.  See the 'Known Issues' section for more information.

   **NOTE:** Adding a platform to the project also installs the full set of plugins listed in the `config.xml` file. Run the `cordova plugin ls` command to retrieve the list from the `config.xml` file.
   
2. Add additional plugins that you want to use in your mobile application.
   - `cordova plugin add [plugin-id]` to install the latest available version of the plugin.
   - `cordova plugin add [plugin-id]@[plugin-version]` to install a specific version of the plugin.
   
   For example:
   - `cordova plugin add cordova-plugin-x-toast` would install the latest version of the Cordova toast plugin.
   - `cordova plugin add cordova-plugin-x-toast@2.5.0` would install version 2.5.0 of the Cordova toast plugin.
   
    **NOTES:** 
   
   - See [Apache Cordova's documentation](https://cordova.apache.org/docs/en/9.x/reference/cordova-cli/index.html#cordova-plugin-command) for more information about the `cordova plugin add` command.
   - For iOS, ensure plugins added to the project do not reference UIWebView.  Apple currently does not accept new applications that use UIWebView, and will stop accepting updates to existing applications that use UIWebView in December 2020.

3. [Optional] Upgrade previously added plugins by first removing the plugin and adding it back.
   - `cordova plugin rm [plugin-id]`
   - `cordova plugin add [plugin-id]`

4. Build the application using command-line flags or a `build.json` file. If you create a `build.json` file, it should reside in the root directory of your project. Change `--release` to `--debug` to build a debug version of the application.
    - iOS
    
      - Update \[projectRoot\]/config.xml document
         - Determine what type of application id is defined in the iOS provisioning profile that will be used for signing the application. If the application id ends with a '\*', it is a wildcard application id type.  If it does not end with a '\*', it is an explicit application id type. 

         - Methods for determining the application id type defined in the iOS provisioning profile:
            ###### Use the [Apple Developer portal](https://developer.apple.com)
            1. Login to your account
            2. Navigate to the 'Certificates, Identifiers & Profiles' and then to the 'Profiles' section of the page
            3. Select the profile you're using and then locate the 'App ID' property.  The value for this property is shown in the form of \[appIdName\](\[`appId`\]).  For example, 'MyWildcardAppId (`com.company.foo.*`)' and 'MyExplicitAppId (`com.company.bar`)'.
            ###### Use a text editor
            1. Locate the installed provisioning profile on your file system and open it in a text editor.  Installed profiles are located in the ~/Library/MobileDevice/Provisioning Profiles/ folder.
            2. Search the document for a \<key\> element having a value of 'application-identifier'.
            3. The \<string\> element immediately after the 'application-identifier' key contains the application id.  This value is of the form \[teamIdentifier\].\[`appId`\].  For example, '1A2B3C4D5E.`com.company.foo.*`' and '1A2B3C4D5E.`com.company.bar`'.

         - Set the 'id' attribute of the '\<widget\>' element in the config.xml document to an application id that satisfies the criteria specified by the application id.

           Examples:
            <table>
            <tr>
                <th>Profile Application Id Type</th>
                <th>Profile Application Id Value</th>
                <th>Config.xml 'id' attribute value</th>
                <th>Comments</th></tr>
            <tr>
                <td>Explicit</td>
                <td>com.company.foo</td><td>com.company.foo</td>
                <td>The id value in config.xml must match the id value in the profile when the type is explicit.</td>
            </tr>
            <tr>
                <td>Wildcard</td><td>com.company.foo.*</td>
                <td>
                    <ul>
                        <li>com.company.foo.MyAppName
                        <li>com.company.foo.bar.baz.MyAppName
                    </ul>
                </td>
                <td>The id value in config.xml must satisfy the wildcard pattern specified in the profile value.  Note that the value in config.xml must not end with the wildcard ('*') character.</td>
            </tr>
            </table>

            <b>NOTE:  This is the <u>only</u> supported manual update of config.xml.  It is highly recommended that no additional manual updates are made to this file.</b>

      - Use a `build.json` file with the signing configuration.  
      `cordova build ios --device --release` 
      
      - Use command-line flags.  
      `cordova build ios --device --release --codeSignIdentity=[signingIdentity] --provisioningProfile=[provisioningProfileUUID]`  
      See [Apache Cordova's documentation](https://cordova.apache.org/docs/en/dev/guide/platforms/ios/index.html#using-flags) for more information about the command-line flags and their values to build for iOS.

   - Android
      -  Use a `build.json` file with the signing configuration.  
      `cordova build android --device --release`

      - Use command-line flags.  
      `cordova build android --device --release --keystore=[path/to/keystore/file] --storePassword=[password]`  
      See [Apache Cordova's documentation](https://cordova.apache.org/docs/en/dev/guide/platforms/android/index.html#using-flags) for more information about the command-line flags and their values to build for Android.
      
5. Upload the APK or IPA file that the build generates to your mobile application in Oracle Visual Builder. For more information, see [Oracle Visual Builder's documentation]( http://docs.oracle.com/pls/topic/lookup?ctx=en/cloud/paas/app-builder-cloud&id=VBCDG-GUID-E558B9DF-AA52-4DF4-867C-7BDEDD689C1D).       

### Known Issues
#### Oracle Cloud Authentication 
If the mobile application uses Oracle Cloud authentication, and you build the template for both iOS and Android platforms, you must add the Android platform to your Cordova project first and then add the iOS platform. Failing to do this will result in the Android application hanging after login.