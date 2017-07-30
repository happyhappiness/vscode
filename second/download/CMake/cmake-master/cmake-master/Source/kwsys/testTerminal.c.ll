; ModuleID = '/data/download/cmake/cmake-master/Source/kwsys/testTerminal.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@stdout = external global %struct._IO_FILE*, align 8
@.str = private unnamed_addr constant [10 x i8] c"Hello %s!\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"World\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @testTerminal(i32 %argc, i8** %argv) #0 !dbg !31 {
entry:
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !42, metadata !43), !dbg !44
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !45, metadata !43), !dbg !46
  %0 = load i32, i32* %argc.addr, align 4, !dbg !47
  %1 = load i8**, i8*** %argv.addr, align 8, !dbg !48
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !49
  call void (i32, %struct._IO_FILE*, i8*, ...) @cmsysTerminal_cfprintf(i32 1108, %struct._IO_FILE* %2, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0)), !dbg !50
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !51
  %call = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %3, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0)), !dbg !52
  ret i32 0, !dbg !53
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @cmsysTerminal_cfprintf(i32, %struct._IO_FILE*, i8*, ...) #2

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!39, !40}
!llvm.ident = !{!41}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !30)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/kwsys/testTerminal.c", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "cmsysTerminal_Color_e", file: !4, line: 96, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/cmsys/Terminal.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29}
!6 = !DIEnumerator(name: "cmsysTerminal_Color_Normal", value: 0)
!7 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundBlack", value: 1)
!8 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundRed", value: 2)
!9 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundGreen", value: 3)
!10 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundYellow", value: 4)
!11 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundBlue", value: 5)
!12 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundMagenta", value: 6)
!13 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundCyan", value: 7)
!14 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundWhite", value: 8)
!15 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundMask", value: 15)
!16 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundBlack", value: 16)
!17 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundRed", value: 32)
!18 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundGreen", value: 48)
!19 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundYellow", value: 64)
!20 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundBlue", value: 80)
!21 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundMagenta", value: 96)
!22 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundCyan", value: 112)
!23 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundWhite", value: 128)
!24 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundMask", value: 240)
!25 = !DIEnumerator(name: "cmsysTerminal_Color_ForegroundBold", value: 256)
!26 = !DIEnumerator(name: "cmsysTerminal_Color_BackgroundBold", value: 512)
!27 = !DIEnumerator(name: "cmsysTerminal_Color_AssumeTTY", value: 1024)
!28 = !DIEnumerator(name: "cmsysTerminal_Color_AssumeVT100", value: 2048)
!29 = !DIEnumerator(name: "cmsysTerminal_Color_AttributeMask", value: 3840)
!30 = !{!31}
!31 = distinct !DISubprogram(name: "testTerminal", scope: !1, file: !1, line: 12, type: !32, isLocal: false, isDefinition: true, scopeLine: 13, flags: DIFlagPrototyped, isOptimized: false, variables: !38)
!32 = !DISubroutineType(types: !33)
!33 = !{!34, !34, !35}
!34 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!38 = !{}
!39 = !{i32 2, !"Dwarf Version", i32 4}
!40 = !{i32 2, !"Debug Info Version", i32 3}
!41 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!42 = !DILocalVariable(name: "argc", arg: 1, scope: !31, file: !1, line: 12, type: !34)
!43 = !DIExpression()
!44 = !DILocation(line: 12, column: 22, scope: !31)
!45 = !DILocalVariable(name: "argv", arg: 2, scope: !31, file: !1, line: 12, type: !35)
!46 = !DILocation(line: 12, column: 34, scope: !31)
!47 = !DILocation(line: 14, column: 9, scope: !31)
!48 = !DILocation(line: 15, column: 9, scope: !31)
!49 = !DILocation(line: 19, column: 26, scope: !31)
!50 = !DILocation(line: 16, column: 3, scope: !31)
!51 = !DILocation(line: 20, column: 11, scope: !31)
!52 = !DILocation(line: 20, column: 3, scope: !31)
!53 = !DILocation(line: 21, column: 3, scope: !31)
