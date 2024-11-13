using System.IO;
using Sharpmake;

//Sharpmake.Application.exe /sources('main.sharpmake.cs')
// C++ project classes must inherit the Project class
[Generate]
public class CascadeEngine : Project
{
    public CascadeEngine()
    {
        //Name of the project
        Name = "Engine";
        
        // The directory that contains the source code we want to build 
        //sharpmakecspath is the path to the sharpmake script
        SourceRootPath = @"[project.SharpmakeCsPath]\..\Source\Engine";
        
        // Specify the targets for which we want to generate a configuration
        // for. Instead of creating multiple targets manually here, we can
        // use the binary OR operator to define multiple targets at once.
        // Sharpmake will generate all combinations possible and generate a
        // target for it.
        //
        // The code below is the same as creating 4 separate targets having
        // those flag combinations:
        //    * Platform.win32, DevEnv.vs2015, Optimization.Debug
        //    * Platform.win32, DevEnv.vs2015, Optimization.Release
        //    * Platform.win64, DevEnv.vs2015, Optimization.Debug
        //    * Platform.win64, DevEnv.vs2015, Optimization.Release

        AddTargets(new Target
        (
            Platform.win32 | Platform.win64,
            
            DevEnv.vs2022,
            
            Optimization.Debug | Optimization.Release
        ));

       
    }
    
    // Sets the properties of each configuration (conf) according to the target.
//
// This method is called once for every target specified by AddTargets. Since
// we only want vs2015 targets and we want 32- and 64-bit targets, each having
// a debug and a release version, we have 1 x 2 x 2 targets to configure, so it
// will be called 4 times.
//
// If we had instead specified vs2012 | vs2015 | vs2017 it would have been
// called 12 times. (3 x 2 x 2)
    [Configure]
    public void ConfigureAll(Project.Configuration conf, Target target)
    {
        //specify where the generated project will be
        conf.ProjectPath = @"[project.SharpmakeCsPath]\..";

        //Intermediate files
        conf.IntermediatePath = @"[project.SharpmakeCsPath]\..\Intermediate";

        //Binaries
        conf.TargetPath = @"[project.SharpmakeCsPath]\..\Binaries";
        
        //cpp standard and warning level + warnings == errors
        conf.AdditionalCompilerOptions.Add("/std:c++20");
        conf.AdditionalCompilerOptions.Add("/W4");

        //Set the Linker Subsystem to Windows (default is console)
        conf.Options.Add(Sharpmake.Options.Vc.Linker.SubSystem.Windows);

        // Include paths
       //conf.IncludePaths.Add(SourceRootPath);

        // Add source files recursively from the Engine folder
        //conf.AddSourceFiles(SourceRootPath + @"\**\*");
    }
}



//Represents the solution that will be generated and that will contain the
//project with the sample code
[Generate]
public class CascadeSolution : Solution
{
    public CascadeSolution()
    {
        Name = "CascadeEngine";
        
        // As with the projcet, define which target this solution builds for.
        //It's usually the same thing.
        AddTargets(new Target
        (
            Platform.win32 | Platform.win64,
            DevEnv.vs2022,
            Optimization.Debug | Optimization.Release
        ));
    }
    
    // Configure for all 4 generated targets. Note that the type of the
    // configuration object is of type Solution.Configuration this time.
    // (Instead of Project.Configuration.)
    [Configure]
    public void ConfigureAll(Solution.Configuration conf, Target target)
    {
        //Puts the generated solution in the /generated folder too
        conf.SolutionPath = @"[solution.SharpmakeCsPath]\..";
        conf.SolutionFileName = "CascadeEngineSolution";
        
        // Adds the project described by BasicsProject into the solution.
        // Note that this is done in the configuration, so you can generate
        // solutions that contain different projects based on their target.
        //
        // You could, for example, exclude a project that only supports 64-bit
        // from the 32-bit targets.
        conf.AddProject<CascadeEngine>(target);
    }
    
}

public static class Main
{
    [Sharpmake.Main]
    public static void SharpmakeMain(Sharpmake.Arguments arguments)
    {
        //Tells Sharpmake to generate the solution described by BasicsSolution
        arguments.Generate<CascadeSolution>();
        
    }
}