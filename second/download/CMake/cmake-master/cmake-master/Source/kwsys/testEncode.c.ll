; ModuleID = '/data/download/cmake/cmake-master/Source/kwsys/testEncode.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.cmsysMD5_s = type opaque

@testMD5input1 = internal constant [87 x i8] c"  A quick brown fox jumps over the lazy dog.\0A  This is sample text for MD5 sum input.\0A\00", align 16
@.str = private unnamed_addr constant [49 x i8] c"md5sum 1: expected [%s]\0A               got [%s]\0A\00", align 1
@testMD5output1 = internal constant [33 x i8] c"8f146af46ed4f267921bb937d4d3500c\00", align 16
@testMD5input2 = internal constant [29 x i8] c"the cow jumped over the moon\00", align 16
@.str.1 = private unnamed_addr constant [49 x i8] c"md5sum 2: expected [%s]\0A               got [%s]\0A\00", align 1
@testMD5output2 = internal constant [33 x i8] c"a2ad137b746138fae4e5adca9c85d3ae\00", align 16

; Function Attrs: nounwind uwtable
define i32 @testEncode(i32 %argc, i8** %argv) #0 !dbg !4 {
entry:
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %result = alloca i32, align 4
  %md5 = alloca %struct.cmsysMD5_s*, align 8
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !41, metadata !42), !dbg !43
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !44, metadata !42), !dbg !45
  call void @llvm.dbg.declare(metadata i32* %result, metadata !46, metadata !42), !dbg !47
  store i32 0, i32* %result, align 4, !dbg !47
  %0 = load i32, i32* %argc.addr, align 4, !dbg !48
  %1 = load i8**, i8*** %argv.addr, align 8, !dbg !49
  call void @llvm.dbg.declare(metadata %struct.cmsysMD5_s** %md5, metadata !50, metadata !42), !dbg !52
  %call = call %struct.cmsysMD5_s* @cmsysMD5_New(), !dbg !53
  store %struct.cmsysMD5_s* %call, %struct.cmsysMD5_s** %md5, align 8, !dbg !52
  %2 = load %struct.cmsysMD5_s*, %struct.cmsysMD5_s** %md5, align 8, !dbg !54
  %call1 = call i32 @testMD5_1(%struct.cmsysMD5_s* %2), !dbg !55
  %3 = load i32, i32* %result, align 4, !dbg !56
  %or = or i32 %3, %call1, !dbg !56
  store i32 %or, i32* %result, align 4, !dbg !56
  %4 = load %struct.cmsysMD5_s*, %struct.cmsysMD5_s** %md5, align 8, !dbg !57
  %call2 = call i32 @testMD5_2(%struct.cmsysMD5_s* %4), !dbg !58
  %5 = load i32, i32* %result, align 4, !dbg !59
  %or3 = or i32 %5, %call2, !dbg !59
  store i32 %or3, i32* %result, align 4, !dbg !59
  %6 = load %struct.cmsysMD5_s*, %struct.cmsysMD5_s** %md5, align 8, !dbg !60
  call void @cmsysMD5_Delete(%struct.cmsysMD5_s* %6), !dbg !61
  %7 = load i32, i32* %result, align 4, !dbg !62
  ret i32 %7, !dbg !63
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare %struct.cmsysMD5_s* @cmsysMD5_New() #2

; Function Attrs: nounwind uwtable
define internal i32 @testMD5_1(%struct.cmsysMD5_s* %md5) #0 !dbg !11 {
entry:
  %md5.addr = alloca %struct.cmsysMD5_s*, align 8
  %md5out = alloca [33 x i8], align 16
  store %struct.cmsysMD5_s* %md5, %struct.cmsysMD5_s** %md5.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cmsysMD5_s** %md5.addr, metadata !64, metadata !42), !dbg !65
  call void @llvm.dbg.declare(metadata [33 x i8]* %md5out, metadata !66, metadata !42), !dbg !68
  %0 = load %struct.cmsysMD5_s*, %struct.cmsysMD5_s** %md5.addr, align 8, !dbg !69
  call void @cmsysMD5_Initialize(%struct.cmsysMD5_s* %0), !dbg !70
  %1 = load %struct.cmsysMD5_s*, %struct.cmsysMD5_s** %md5.addr, align 8, !dbg !71
  call void @cmsysMD5_Append(%struct.cmsysMD5_s* %1, i8* getelementptr inbounds ([87 x i8], [87 x i8]* @testMD5input1, i32 0, i32 0), i32 -1), !dbg !72
  %2 = load %struct.cmsysMD5_s*, %struct.cmsysMD5_s** %md5.addr, align 8, !dbg !73
  %arraydecay = getelementptr inbounds [33 x i8], [33 x i8]* %md5out, i32 0, i32 0, !dbg !74
  call void @cmsysMD5_FinalizeHex(%struct.cmsysMD5_s* %2, i8* %arraydecay), !dbg !75
  %arrayidx = getelementptr inbounds [33 x i8], [33 x i8]* %md5out, i64 0, i64 32, !dbg !76
  store i8 0, i8* %arrayidx, align 16, !dbg !77
  %arraydecay1 = getelementptr inbounds [33 x i8], [33 x i8]* %md5out, i32 0, i32 0, !dbg !78
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([33 x i8], [33 x i8]* @testMD5output1, i32 0, i32 0), i8* %arraydecay1), !dbg !79
  %arraydecay2 = getelementptr inbounds [33 x i8], [33 x i8]* %md5out, i32 0, i32 0, !dbg !80
  %call3 = call i32 @strcmp(i8* %arraydecay2, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @testMD5output1, i32 0, i32 0)) #4, !dbg !81
  %cmp = icmp ne i32 %call3, 0, !dbg !82
  %cond = select i1 %cmp, i32 1, i32 0, !dbg !83
  ret i32 %cond, !dbg !84
}

; Function Attrs: nounwind uwtable
define internal i32 @testMD5_2(%struct.cmsysMD5_s* %md5) #0 !dbg !18 {
entry:
  %md5.addr = alloca %struct.cmsysMD5_s*, align 8
  %digest = alloca [16 x i8], align 16
  %md5out = alloca [33 x i8], align 16
  store %struct.cmsysMD5_s* %md5, %struct.cmsysMD5_s** %md5.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cmsysMD5_s** %md5.addr, metadata !85, metadata !42), !dbg !86
  call void @llvm.dbg.declare(metadata [16 x i8]* %digest, metadata !87, metadata !42), !dbg !91
  call void @llvm.dbg.declare(metadata [33 x i8]* %md5out, metadata !92, metadata !42), !dbg !93
  %0 = load %struct.cmsysMD5_s*, %struct.cmsysMD5_s** %md5.addr, align 8, !dbg !94
  call void @cmsysMD5_Initialize(%struct.cmsysMD5_s* %0), !dbg !95
  %1 = load %struct.cmsysMD5_s*, %struct.cmsysMD5_s** %md5.addr, align 8, !dbg !96
  call void @cmsysMD5_Append(%struct.cmsysMD5_s* %1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @testMD5input2, i32 0, i32 0), i32 28), !dbg !97
  %2 = load %struct.cmsysMD5_s*, %struct.cmsysMD5_s** %md5.addr, align 8, !dbg !98
  %arraydecay = getelementptr inbounds [16 x i8], [16 x i8]* %digest, i32 0, i32 0, !dbg !99
  call void @cmsysMD5_Finalize(%struct.cmsysMD5_s* %2, i8* %arraydecay), !dbg !100
  %arraydecay1 = getelementptr inbounds [16 x i8], [16 x i8]* %digest, i32 0, i32 0, !dbg !101
  %arraydecay2 = getelementptr inbounds [33 x i8], [33 x i8]* %md5out, i32 0, i32 0, !dbg !102
  call void @cmsysMD5_DigestToHex(i8* %arraydecay1, i8* %arraydecay2), !dbg !103
  %arrayidx = getelementptr inbounds [33 x i8], [33 x i8]* %md5out, i64 0, i64 32, !dbg !104
  store i8 0, i8* %arrayidx, align 16, !dbg !105
  %arraydecay3 = getelementptr inbounds [33 x i8], [33 x i8]* %md5out, i32 0, i32 0, !dbg !106
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([33 x i8], [33 x i8]* @testMD5output2, i32 0, i32 0), i8* %arraydecay3), !dbg !107
  %arraydecay4 = getelementptr inbounds [33 x i8], [33 x i8]* %md5out, i32 0, i32 0, !dbg !108
  %call5 = call i32 @strcmp(i8* %arraydecay4, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @testMD5output2, i32 0, i32 0)) #4, !dbg !109
  %cmp = icmp ne i32 %call5, 0, !dbg !110
  %cond = select i1 %cmp, i32 1, i32 0, !dbg !111
  ret i32 %cond, !dbg !112
}

declare void @cmsysMD5_Delete(%struct.cmsysMD5_s*) #2

declare void @cmsysMD5_Initialize(%struct.cmsysMD5_s*) #2

declare void @cmsysMD5_Append(%struct.cmsysMD5_s*, i8*, i32) #2

declare void @cmsysMD5_FinalizeHex(%struct.cmsysMD5_s*, i8*) #2

declare i32 @printf(i8*, ...) #2

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #3

declare void @cmsysMD5_Finalize(%struct.cmsysMD5_s*, i8*) #2

declare void @cmsysMD5_DigestToHex(i8*, i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!38, !39}
!llvm.ident = !{!40}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3, globals: !19)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/kwsys/testEncode.c", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!2 = !{}
!3 = !{!4, !11, !18}
!4 = distinct !DISubprogram(name: "testEncode", scope: !1, file: !1, line: 52, type: !5, isLocal: false, isDefinition: true, scopeLine: 53, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !7, !8}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!11 = distinct !DISubprogram(name: "testMD5_1", scope: !1, file: !1, line: 24, type: !12, isLocal: true, isDefinition: true, scopeLine: 25, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!12 = !DISubroutineType(types: !13)
!13 = !{!7, !14}
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DIDerivedType(tag: DW_TAG_typedef, name: "cmsysMD5", file: !16, line: 35, baseType: !17)
!16 = !DIFile(filename: "/data/download/cmake/cmake-master/Source/cmsys/MD5.h", directory: "/data/download/cmake/cmake-master/Source/kwsys")
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "cmsysMD5_s", file: !16, line: 35, flags: DIFlagFwdDecl)
!18 = distinct !DISubprogram(name: "testMD5_2", scope: !1, file: !1, line: 37, type: !12, isLocal: true, isDefinition: true, scopeLine: 38, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!19 = !{!20, !26, !31, !33, !37}
!20 = !DIGlobalVariable(name: "testMD5input1", scope: !0, file: !1, line: 15, type: !21, isLocal: true, isDefinition: true, variable: [87 x i8]* @testMD5input1)
!21 = !DICompositeType(tag: DW_TAG_array_type, baseType: !22, size: 696, align: 8, elements: !24)
!22 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !23)
!23 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!24 = !{!25}
!25 = !DISubrange(count: 87)
!26 = !DIGlobalVariable(name: "testMD5output1", scope: !0, file: !1, line: 18, type: !27, isLocal: true, isDefinition: true, variable: [33 x i8]* @testMD5output1)
!27 = !DICompositeType(tag: DW_TAG_array_type, baseType: !28, size: 264, align: 8, elements: !29)
!28 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !10)
!29 = !{!30}
!30 = !DISubrange(count: 33)
!31 = !DIGlobalVariable(name: "testMD5input2len", scope: !0, file: !1, line: 20, type: !32, isLocal: true, isDefinition: true, variable: i32 28)
!32 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !7)
!33 = !DIGlobalVariable(name: "testMD5input2", scope: !0, file: !1, line: 21, type: !34, isLocal: true, isDefinition: true, variable: [29 x i8]* @testMD5input2)
!34 = !DICompositeType(tag: DW_TAG_array_type, baseType: !22, size: 232, align: 8, elements: !35)
!35 = !{!36}
!36 = !DISubrange(count: 29)
!37 = !DIGlobalVariable(name: "testMD5output2", scope: !0, file: !1, line: 22, type: !27, isLocal: true, isDefinition: true, variable: [33 x i8]* @testMD5output2)
!38 = !{i32 2, !"Dwarf Version", i32 4}
!39 = !{i32 2, !"Debug Info Version", i32 3}
!40 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!41 = !DILocalVariable(name: "argc", arg: 1, scope: !4, file: !1, line: 52, type: !7)
!42 = !DIExpression()
!43 = !DILocation(line: 52, column: 20, scope: !4)
!44 = !DILocalVariable(name: "argv", arg: 2, scope: !4, file: !1, line: 52, type: !8)
!45 = !DILocation(line: 52, column: 32, scope: !4)
!46 = !DILocalVariable(name: "result", scope: !4, file: !1, line: 54, type: !7)
!47 = !DILocation(line: 54, column: 7, scope: !4)
!48 = !DILocation(line: 55, column: 9, scope: !4)
!49 = !DILocation(line: 56, column: 9, scope: !4)
!50 = !DILocalVariable(name: "md5", scope: !51, file: !1, line: 60, type: !14)
!51 = distinct !DILexicalBlock(scope: !4, file: !1, line: 59, column: 3)
!52 = !DILocation(line: 60, column: 15, scope: !51)
!53 = !DILocation(line: 60, column: 21, scope: !51)
!54 = !DILocation(line: 61, column: 25, scope: !51)
!55 = !DILocation(line: 61, column: 15, scope: !51)
!56 = !DILocation(line: 61, column: 12, scope: !51)
!57 = !DILocation(line: 62, column: 25, scope: !51)
!58 = !DILocation(line: 62, column: 15, scope: !51)
!59 = !DILocation(line: 62, column: 12, scope: !51)
!60 = !DILocation(line: 63, column: 21, scope: !51)
!61 = !DILocation(line: 63, column: 5, scope: !51)
!62 = !DILocation(line: 66, column: 10, scope: !4)
!63 = !DILocation(line: 66, column: 3, scope: !4)
!64 = !DILocalVariable(name: "md5", arg: 1, scope: !11, file: !1, line: 24, type: !14)
!65 = !DILocation(line: 24, column: 32, scope: !11)
!66 = !DILocalVariable(name: "md5out", scope: !11, file: !1, line: 26, type: !67)
!67 = !DICompositeType(tag: DW_TAG_array_type, baseType: !10, size: 264, align: 8, elements: !29)
!68 = !DILocation(line: 26, column: 8, scope: !11)
!69 = !DILocation(line: 27, column: 23, scope: !11)
!70 = !DILocation(line: 27, column: 3, scope: !11)
!71 = !DILocation(line: 28, column: 19, scope: !11)
!72 = !DILocation(line: 28, column: 3, scope: !11)
!73 = !DILocation(line: 29, column: 24, scope: !11)
!74 = !DILocation(line: 29, column: 29, scope: !11)
!75 = !DILocation(line: 29, column: 3, scope: !11)
!76 = !DILocation(line: 30, column: 3, scope: !11)
!77 = !DILocation(line: 30, column: 14, scope: !11)
!78 = !DILocation(line: 33, column: 26, scope: !11)
!79 = !DILocation(line: 31, column: 3, scope: !11)
!80 = !DILocation(line: 34, column: 18, scope: !11)
!81 = !DILocation(line: 34, column: 11, scope: !11)
!82 = !DILocation(line: 34, column: 42, scope: !11)
!83 = !DILocation(line: 34, column: 10, scope: !11)
!84 = !DILocation(line: 34, column: 3, scope: !11)
!85 = !DILocalVariable(name: "md5", arg: 1, scope: !18, file: !1, line: 37, type: !14)
!86 = !DILocation(line: 37, column: 32, scope: !18)
!87 = !DILocalVariable(name: "digest", scope: !18, file: !1, line: 39, type: !88)
!88 = !DICompositeType(tag: DW_TAG_array_type, baseType: !23, size: 128, align: 8, elements: !89)
!89 = !{!90}
!90 = !DISubrange(count: 16)
!91 = !DILocation(line: 39, column: 17, scope: !18)
!92 = !DILocalVariable(name: "md5out", scope: !18, file: !1, line: 40, type: !67)
!93 = !DILocation(line: 40, column: 8, scope: !18)
!94 = !DILocation(line: 41, column: 23, scope: !18)
!95 = !DILocation(line: 41, column: 3, scope: !18)
!96 = !DILocation(line: 42, column: 19, scope: !18)
!97 = !DILocation(line: 42, column: 3, scope: !18)
!98 = !DILocation(line: 43, column: 21, scope: !18)
!99 = !DILocation(line: 43, column: 26, scope: !18)
!100 = !DILocation(line: 43, column: 3, scope: !18)
!101 = !DILocation(line: 44, column: 24, scope: !18)
!102 = !DILocation(line: 44, column: 32, scope: !18)
!103 = !DILocation(line: 44, column: 3, scope: !18)
!104 = !DILocation(line: 45, column: 3, scope: !18)
!105 = !DILocation(line: 45, column: 14, scope: !18)
!106 = !DILocation(line: 48, column: 26, scope: !18)
!107 = !DILocation(line: 46, column: 3, scope: !18)
!108 = !DILocation(line: 49, column: 18, scope: !18)
!109 = !DILocation(line: 49, column: 11, scope: !18)
!110 = !DILocation(line: 49, column: 42, scope: !18)
!111 = !DILocation(line: 49, column: 10, scope: !18)
!112 = !DILocation(line: 49, column: 3, scope: !18)
