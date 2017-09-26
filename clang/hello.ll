; ModuleID = 'hello.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [37 x i8] c"%d * %d < 100, m:%p, n:%d, eval:%d.\0A\00", align 1
@.str.1 = private unnamed_addr constant [16 x i8] c"%d * %d >= 100\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @_Z3addii(i32 %i, i32 %j) #0 !dbg !4 {
entry:
  %i.addr = alloca i32, align 4
  %j.addr = alloca i32, align 4
  store i32 %i, i32* %i.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %i.addr, metadata !27, metadata !28), !dbg !29
  store i32 %j, i32* %j.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %j.addr, metadata !30, metadata !28), !dbg !31
  %0 = load i32, i32* %i.addr, align 4, !dbg !32
  %1 = load i32, i32* %j.addr, align 4, !dbg !33
  %add = add nsw i32 %0, %1, !dbg !34
  ret i32 %add, !dbg !35
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @_Z3mulii(i32 %i, i32 %j) #0 !dbg !8 {
entry:
  %i.addr = alloca i32, align 4
  %j.addr = alloca i32, align 4
  store i32 %i, i32* %i.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %i.addr, metadata !36, metadata !28), !dbg !37
  store i32 %j, i32* %j.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %j.addr, metadata !38, metadata !28), !dbg !39
  %0 = load i32, i32* %i.addr, align 4, !dbg !40
  %1 = load i32, i32* %j.addr, align 4, !dbg !41
  %mul = mul nsw i32 %0, %1, !dbg !42
  ret i32 %mul, !dbg !43
}

; Function Attrs: nounwind uwtable
define i32 @_Z4evalRi(i32* dereferenceable(4) %i) #0 !dbg !9 {
entry:
  %i.addr = alloca i32*, align 8
  store i32* %i, i32** %i.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %i.addr, metadata !44, metadata !28), !dbg !45
  %0 = load i32*, i32** %i.addr, align 8, !dbg !46
  %1 = load i32, i32* %0, align 4, !dbg !46
  %cmp = icmp sgt i32 %1, 10, !dbg !47
  %conv = zext i1 %cmp to i32, !dbg !46
  ret i32 %conv, !dbg !48
}

; Function Attrs: nounwind uwtable
define double @_Z4evald(double %i) #0 !dbg !13 {
entry:
  %i.addr = alloca double, align 8
  store double %i, double* %i.addr, align 8
  call void @llvm.dbg.declare(metadata double* %i.addr, metadata !49, metadata !28), !dbg !50
  %0 = load double, double* %i.addr, align 8, !dbg !51
  %cmp = fcmp ogt double %0, 1.000000e+01, !dbg !52
  %conv = uitofp i1 %cmp to double, !dbg !51
  ret double %conv, !dbg !53
}

; Function Attrs: nounwind uwtable
define i32 @_Z3ptrPi(i32* %i) #0 !dbg !17 {
entry:
  %i.addr = alloca i32*, align 8
  store i32* %i, i32** %i.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %i.addr, metadata !54, metadata !28), !dbg !55
  %0 = load i32*, i32** %i.addr, align 8, !dbg !56
  %1 = load i32, i32* %0, align 4, !dbg !57
  ret i32 %1, !dbg !58
}

; Function Attrs: norecurse uwtable
define i32 @main() #2 !dbg !21 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %m = alloca i32*, align 8
  %n = alloca i32, align 4
  %k = alloca double, align 8
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %a, metadata !59, metadata !28), !dbg !60
  store i32 10, i32* %a, align 4, !dbg !60
  call void @llvm.dbg.declare(metadata i32* %b, metadata !61, metadata !28), !dbg !62
  store i32 10, i32* %b, align 4, !dbg !62
  call void @llvm.dbg.declare(metadata i32* %i, metadata !63, metadata !28), !dbg !64
  %0 = load i32, i32* %a, align 4, !dbg !65
  %1 = load i32, i32* %b, align 4, !dbg !66
  %call = call i32 @_Z3addii(i32 %0, i32 %1), !dbg !67
  store i32 %call, i32* %i, align 4, !dbg !64
  call void @llvm.dbg.declare(metadata i32* %j, metadata !68, metadata !28), !dbg !69
  %2 = load i32, i32* %a, align 4, !dbg !70
  %3 = load i32, i32* %b, align 4, !dbg !71
  %call1 = call i32 @_Z3mulii(i32 %2, i32 %3), !dbg !72
  store i32 %call1, i32* %j, align 4, !dbg !69
  call void @llvm.dbg.declare(metadata i32** %m, metadata !73, metadata !28), !dbg !74
  call void @llvm.dbg.declare(metadata i32* %n, metadata !75, metadata !28), !dbg !76
  call void @llvm.dbg.declare(metadata double* %k, metadata !77, metadata !28), !dbg !78
  store double 0.000000e+00, double* %k, align 8, !dbg !78
  %4 = load i32, i32* %i, align 4, !dbg !79
  %5 = load i32, i32* %j, align 4, !dbg !81
  %mul = mul nsw i32 %4, %5, !dbg !82
  %cmp = icmp slt i32 %mul, 100, !dbg !83
  br i1 %cmp, label %if.then, label %if.else, !dbg !84

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %i, align 4, !dbg !85
  %conv = sitofp i32 %6 to double, !dbg !85
  %7 = load i32, i32* %i, align 4, !dbg !88
  %8 = load i32, i32* %j, align 4, !dbg !89
  %add = add nsw i32 %7, %8, !dbg !90
  %conv2 = sitofp i32 %add to double, !dbg !88
  %9 = load double, double* %k, align 8, !dbg !91
  %add3 = fadd double %conv2, %9, !dbg !92
  %call4 = call double @_Z4evald(double %add3), !dbg !93
  %add5 = fadd double %conv, %call4, !dbg !94
  %10 = load i32, i32* %j, align 4, !dbg !95
  %conv6 = sitofp i32 %10 to double, !dbg !95
  %add7 = fadd double %add5, %conv6, !dbg !96
  %tobool = fcmp une double %add7, 0.000000e+00, !dbg !85
  br i1 %tobool, label %if.then8, label %if.end, !dbg !97

if.then8:                                         ; preds = %if.then
  %11 = load i32*, i32** %m, align 8, !dbg !98
  %call9 = call i32 @_Z3ptrPi(i32* %11), !dbg !100
  store i32 %call9, i32* %i, align 4, !dbg !101
  %12 = load i32, i32* %i, align 4, !dbg !102
  %13 = load i32, i32* %j, align 4, !dbg !103
  %14 = load i32*, i32** %m, align 8, !dbg !104
  %15 = load i32, i32* %n, align 4, !dbg !105
  %call10 = call i32 @_Z4evalRi(i32* dereferenceable(4) %i), !dbg !106
  %call11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str, i32 0, i32 0), i32 %12, i32 %13, i32* %14, i32 %15, i32 %call10), !dbg !107
  %call12 = call i32 @_Z4evalRi(i32* dereferenceable(4) %n), !dbg !108
  store i32 %call12, i32* %j, align 4, !dbg !109
  br label %if.end, !dbg !110

if.end:                                           ; preds = %if.then8, %if.then
  %16 = load double, double* %k, align 8, !dbg !111
  %call13 = call double @_Z4evald(double %16), !dbg !112
  br label %if.end15, !dbg !113

if.else:                                          ; preds = %entry
  %17 = load i32, i32* %i, align 4, !dbg !114
  %18 = load i32, i32* %j, align 4, !dbg !116
  %call14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.1, i32 0, i32 0), i32 %17, i32 %18), !dbg !117
  br label %if.end15

if.end15:                                         ; preds = %if.else, %if.end
  ret i32 0, !dbg !118
}

declare i32 @printf(i8*, ...) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { norecurse uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!24, !25}
!llvm.ident = !{!26}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "hello.cpp", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/clang")
!2 = !{}
!3 = !{!4, !8, !9, !13, !17, !21}
!4 = distinct !DISubprogram(name: "add", linkageName: "_Z3addii", scope: !1, file: !1, line: 2, type: !5, isLocal: false, isDefinition: true, scopeLine: 3, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !7, !7}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = distinct !DISubprogram(name: "mul", linkageName: "_Z3mulii", scope: !1, file: !1, line: 6, type: !5, isLocal: false, isDefinition: true, scopeLine: 7, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!9 = distinct !DISubprogram(name: "eval", linkageName: "_Z4evalRi", scope: !1, file: !1, line: 10, type: !10, isLocal: false, isDefinition: true, scopeLine: 11, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!10 = !DISubroutineType(types: !11)
!11 = !{!7, !12}
!12 = !DIDerivedType(tag: DW_TAG_reference_type, baseType: !7, size: 64, align: 64)
!13 = distinct !DISubprogram(name: "eval", linkageName: "_Z4evald", scope: !1, file: !1, line: 14, type: !14, isLocal: false, isDefinition: true, scopeLine: 15, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!14 = !DISubroutineType(types: !15)
!15 = !{!16, !16}
!16 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!17 = distinct !DISubprogram(name: "ptr", linkageName: "_Z3ptrPi", scope: !1, file: !1, line: 18, type: !18, isLocal: false, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!18 = !DISubroutineType(types: !19)
!19 = !{!7, !20}
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64, align: 64)
!21 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 22, type: !22, isLocal: false, isDefinition: true, scopeLine: 23, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!22 = !DISubroutineType(types: !23)
!23 = !{!7}
!24 = !{i32 2, !"Dwarf Version", i32 4}
!25 = !{i32 2, !"Debug Info Version", i32 3}
!26 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!27 = !DILocalVariable(name: "i", arg: 1, scope: !4, file: !1, line: 2, type: !7)
!28 = !DIExpression()
!29 = !DILocation(line: 2, column: 13, scope: !4)
!30 = !DILocalVariable(name: "j", arg: 2, scope: !4, file: !1, line: 2, type: !7)
!31 = !DILocation(line: 2, column: 20, scope: !4)
!32 = !DILocation(line: 4, column: 9, scope: !4)
!33 = !DILocation(line: 4, column: 13, scope: !4)
!34 = !DILocation(line: 4, column: 11, scope: !4)
!35 = !DILocation(line: 4, column: 2, scope: !4)
!36 = !DILocalVariable(name: "i", arg: 1, scope: !8, file: !1, line: 6, type: !7)
!37 = !DILocation(line: 6, column: 13, scope: !8)
!38 = !DILocalVariable(name: "j", arg: 2, scope: !8, file: !1, line: 6, type: !7)
!39 = !DILocation(line: 6, column: 20, scope: !8)
!40 = !DILocation(line: 8, column: 9, scope: !8)
!41 = !DILocation(line: 8, column: 11, scope: !8)
!42 = !DILocation(line: 8, column: 10, scope: !8)
!43 = !DILocation(line: 8, column: 2, scope: !8)
!44 = !DILocalVariable(name: "i", arg: 1, scope: !9, file: !1, line: 10, type: !12)
!45 = !DILocation(line: 10, column: 15, scope: !9)
!46 = !DILocation(line: 12, column: 9, scope: !9)
!47 = !DILocation(line: 12, column: 11, scope: !9)
!48 = !DILocation(line: 12, column: 2, scope: !9)
!49 = !DILocalVariable(name: "i", arg: 1, scope: !13, file: !1, line: 14, type: !16)
!50 = !DILocation(line: 14, column: 20, scope: !13)
!51 = !DILocation(line: 16, column: 9, scope: !13)
!52 = !DILocation(line: 16, column: 11, scope: !13)
!53 = !DILocation(line: 16, column: 2, scope: !13)
!54 = !DILocalVariable(name: "i", arg: 1, scope: !17, file: !1, line: 18, type: !20)
!55 = !DILocation(line: 18, column: 14, scope: !17)
!56 = !DILocation(line: 20, column: 10, scope: !17)
!57 = !DILocation(line: 20, column: 9, scope: !17)
!58 = !DILocation(line: 20, column: 2, scope: !17)
!59 = !DILocalVariable(name: "a", scope: !21, file: !1, line: 24, type: !7)
!60 = !DILocation(line: 24, column: 6, scope: !21)
!61 = !DILocalVariable(name: "b", scope: !21, file: !1, line: 25, type: !7)
!62 = !DILocation(line: 25, column: 6, scope: !21)
!63 = !DILocalVariable(name: "i", scope: !21, file: !1, line: 26, type: !7)
!64 = !DILocation(line: 26, column: 6, scope: !21)
!65 = !DILocation(line: 26, column: 14, scope: !21)
!66 = !DILocation(line: 26, column: 17, scope: !21)
!67 = !DILocation(line: 26, column: 10, scope: !21)
!68 = !DILocalVariable(name: "j", scope: !21, file: !1, line: 27, type: !7)
!69 = !DILocation(line: 27, column: 6, scope: !21)
!70 = !DILocation(line: 27, column: 14, scope: !21)
!71 = !DILocation(line: 27, column: 17, scope: !21)
!72 = !DILocation(line: 27, column: 10, scope: !21)
!73 = !DILocalVariable(name: "m", scope: !21, file: !1, line: 28, type: !20)
!74 = !DILocation(line: 28, column: 7, scope: !21)
!75 = !DILocalVariable(name: "n", scope: !21, file: !1, line: 29, type: !7)
!76 = !DILocation(line: 29, column: 6, scope: !21)
!77 = !DILocalVariable(name: "k", scope: !21, file: !1, line: 30, type: !16)
!78 = !DILocation(line: 30, column: 9, scope: !21)
!79 = !DILocation(line: 31, column: 5, scope: !80)
!80 = distinct !DILexicalBlock(scope: !21, file: !1, line: 31, column: 5)
!81 = !DILocation(line: 31, column: 9, scope: !80)
!82 = !DILocation(line: 31, column: 7, scope: !80)
!83 = !DILocation(line: 31, column: 11, scope: !80)
!84 = !DILocation(line: 31, column: 5, scope: !21)
!85 = !DILocation(line: 33, column: 6, scope: !86)
!86 = distinct !DILexicalBlock(scope: !87, file: !1, line: 33, column: 6)
!87 = distinct !DILexicalBlock(scope: !80, file: !1, line: 32, column: 2)
!88 = !DILocation(line: 33, column: 15, scope: !86)
!89 = !DILocation(line: 33, column: 19, scope: !86)
!90 = !DILocation(line: 33, column: 17, scope: !86)
!91 = !DILocation(line: 33, column: 23, scope: !86)
!92 = !DILocation(line: 33, column: 21, scope: !86)
!93 = !DILocation(line: 33, column: 10, scope: !86)
!94 = !DILocation(line: 33, column: 8, scope: !86)
!95 = !DILocation(line: 33, column: 28, scope: !86)
!96 = !DILocation(line: 33, column: 26, scope: !86)
!97 = !DILocation(line: 33, column: 6, scope: !87)
!98 = !DILocation(line: 35, column: 12, scope: !99)
!99 = distinct !DILexicalBlock(scope: !86, file: !1, line: 34, column: 3)
!100 = !DILocation(line: 35, column: 8, scope: !99)
!101 = !DILocation(line: 35, column: 6, scope: !99)
!102 = !DILocation(line: 36, column: 52, scope: !99)
!103 = !DILocation(line: 36, column: 55, scope: !99)
!104 = !DILocation(line: 37, column: 7, scope: !99)
!105 = !DILocation(line: 37, column: 10, scope: !99)
!106 = !DILocation(line: 37, column: 13, scope: !99)
!107 = !DILocation(line: 36, column: 4, scope: !99)
!108 = !DILocation(line: 38, column: 8, scope: !99)
!109 = !DILocation(line: 38, column: 6, scope: !99)
!110 = !DILocation(line: 39, column: 3, scope: !99)
!111 = !DILocation(line: 40, column: 8, scope: !87)
!112 = !DILocation(line: 40, column: 3, scope: !87)
!113 = !DILocation(line: 42, column: 2, scope: !87)
!114 = !DILocation(line: 45, column: 30, scope: !115)
!115 = distinct !DILexicalBlock(scope: !80, file: !1, line: 44, column: 2)
!116 = !DILocation(line: 45, column: 33, scope: !115)
!117 = !DILocation(line: 45, column: 3, scope: !115)
!118 = !DILocation(line: 49, column: 2, scope: !21)
