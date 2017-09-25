; ModuleID = 'hello.bc'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [15 x i8] c"%d * %d < 100\0A\00", align 1
@.str.1 = private unnamed_addr constant [16 x i8] c"%d * %d >= 100\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @_Z3addii(i32 %i, i32 %j) #0 !dbg !4 {
entry:
  %i.addr = alloca i32, align 4
  %j.addr = alloca i32, align 4
  store i32 %i, i32* %i.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %i.addr, metadata !22, metadata !23), !dbg !24
  store i32 %j, i32* %j.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %j.addr, metadata !25, metadata !23), !dbg !26
  %0 = load i32, i32* %i.addr, align 4, !dbg !27
  %1 = load i32, i32* %j.addr, align 4, !dbg !28
  %add = add nsw i32 %0, %1, !dbg !29
  ret i32 %add, !dbg !30
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @_Z3mulii(i32 %i, i32 %j) #0 !dbg !8 {
entry:
  %i.addr = alloca i32, align 4
  %j.addr = alloca i32, align 4
  store i32 %i, i32* %i.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %i.addr, metadata !31, metadata !23), !dbg !32
  store i32 %j, i32* %j.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %j.addr, metadata !33, metadata !23), !dbg !34
  %0 = load i32, i32* %i.addr, align 4, !dbg !35
  %1 = load i32, i32* %j.addr, align 4, !dbg !36
  %mul = mul nsw i32 %0, %1, !dbg !37
  ret i32 %mul, !dbg !38
}

; Function Attrs: nounwind uwtable
define i32 @_Z4evali(i32 %i) #0 !dbg !9 {
entry:
  %i.addr = alloca i32, align 4
  store i32 %i, i32* %i.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %i.addr, metadata !39, metadata !23), !dbg !40
  %0 = load i32, i32* %i.addr, align 4, !dbg !41
  %cmp = icmp sgt i32 %0, 10, !dbg !42
  %conv = zext i1 %cmp to i32, !dbg !41
  ret i32 %conv, !dbg !43
}

; Function Attrs: nounwind uwtable
define double @_Z4evald(double %i) #0 !dbg !12 {
entry:
  %i.addr = alloca double, align 8
  store double %i, double* %i.addr, align 8
  call void @llvm.dbg.declare(metadata double* %i.addr, metadata !44, metadata !23), !dbg !45
  %0 = load double, double* %i.addr, align 8, !dbg !46
  %cmp = fcmp ogt double %0, 1.000000e+01, !dbg !47
  %conv = uitofp i1 %cmp to double, !dbg !46
  ret double %conv, !dbg !48
}

; Function Attrs: norecurse uwtable
define i32 @main() #2 !dbg !16 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %k = alloca double, align 8
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %a, metadata !49, metadata !23), !dbg !50
  store i32 10, i32* %a, align 4, !dbg !50
  call void @llvm.dbg.declare(metadata i32* %b, metadata !51, metadata !23), !dbg !52
  store i32 10, i32* %b, align 4, !dbg !52
  call void @llvm.dbg.declare(metadata i32* %i, metadata !53, metadata !23), !dbg !54
  %0 = load i32, i32* %a, align 4, !dbg !55
  %1 = load i32, i32* %b, align 4, !dbg !56
  %call = call i32 @_Z3addii(i32 %0, i32 %1), !dbg !57
  store i32 %call, i32* %i, align 4, !dbg !54
  call void @llvm.dbg.declare(metadata i32* %j, metadata !58, metadata !23), !dbg !59
  %2 = load i32, i32* %a, align 4, !dbg !60
  %3 = load i32, i32* %b, align 4, !dbg !61
  %call1 = call i32 @_Z3mulii(i32 %2, i32 %3), !dbg !62
  store i32 %call1, i32* %j, align 4, !dbg !59
  call void @llvm.dbg.declare(metadata double* %k, metadata !63, metadata !23), !dbg !64
  store double 0.000000e+00, double* %k, align 8, !dbg !64
  %4 = load i32, i32* %i, align 4, !dbg !65
  %5 = load i32, i32* %j, align 4, !dbg !67
  %mul = mul nsw i32 %4, %5, !dbg !68
  %cmp = icmp slt i32 %mul, 100, !dbg !69
  br i1 %cmp, label %if.then, label %if.else, !dbg !70

if.then:                                          ; preds = %entry
  %6 = load i32, i32* %i, align 4, !dbg !71
  %conv = sitofp i32 %6 to double, !dbg !71
  %7 = load i32, i32* %i, align 4, !dbg !74
  %8 = load i32, i32* %j, align 4, !dbg !75
  %add = add nsw i32 %7, %8, !dbg !76
  %conv2 = sitofp i32 %add to double, !dbg !74
  %9 = load double, double* %k, align 8, !dbg !77
  %add3 = fadd double %conv2, %9, !dbg !78
  %call4 = call double @_Z4evald(double %add3), !dbg !79
  %add5 = fadd double %conv, %call4, !dbg !80
  %10 = load i32, i32* %j, align 4, !dbg !81
  %conv6 = sitofp i32 %10 to double, !dbg !81
  %add7 = fadd double %add5, %conv6, !dbg !82
  %tobool = fcmp une double %add7, 0.000000e+00, !dbg !71
  br i1 %tobool, label %if.then8, label %if.end, !dbg !83

if.then8:                                         ; preds = %if.then
  %11 = load i32, i32* %i, align 4, !dbg !84
  %12 = load i32, i32* %j, align 4, !dbg !85
  %call9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str, i32 0, i32 0), i32 %11, i32 %12), !dbg !86
  br label %if.end, !dbg !86

if.end:                                           ; preds = %if.then8, %if.then
  %13 = load double, double* %k, align 8, !dbg !87
  %call10 = call double @_Z4evald(double %13), !dbg !88
  br label %if.end12, !dbg !89

if.else:                                          ; preds = %entry
  %14 = load i32, i32* %i, align 4, !dbg !90
  %15 = load i32, i32* %j, align 4, !dbg !92
  %call11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.1, i32 0, i32 0), i32 %14, i32 %15), !dbg !93
  br label %if.end12

if.end12:                                         ; preds = %if.else, %if.end
  ret i32 0, !dbg !94
}

declare i32 @printf(i8*, ...) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { norecurse uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!19, !20}
!llvm.ident = !{!21}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "hello.cpp", directory: "/usr/info/code/cpp/LogMonitor/LogMonitor/clang")
!2 = !{}
!3 = !{!4, !8, !9, !12, !16}
!4 = distinct !DISubprogram(name: "add", linkageName: "_Z3addii", scope: !1, file: !1, line: 2, type: !5, isLocal: false, isDefinition: true, scopeLine: 3, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !7, !7}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = distinct !DISubprogram(name: "mul", linkageName: "_Z3mulii", scope: !1, file: !1, line: 6, type: !5, isLocal: false, isDefinition: true, scopeLine: 7, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!9 = distinct !DISubprogram(name: "eval", linkageName: "_Z4evali", scope: !1, file: !1, line: 10, type: !10, isLocal: false, isDefinition: true, scopeLine: 11, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!10 = !DISubroutineType(types: !11)
!11 = !{!7, !7}
!12 = distinct !DISubprogram(name: "eval", linkageName: "_Z4evald", scope: !1, file: !1, line: 14, type: !13, isLocal: false, isDefinition: true, scopeLine: 15, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!13 = !DISubroutineType(types: !14)
!14 = !{!15, !15}
!15 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!16 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 18, type: !17, isLocal: false, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!17 = !DISubroutineType(types: !18)
!18 = !{!7}
!19 = !{i32 2, !"Dwarf Version", i32 4}
!20 = !{i32 2, !"Debug Info Version", i32 3}
!21 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!22 = !DILocalVariable(name: "i", arg: 1, scope: !4, file: !1, line: 2, type: !7)
!23 = !DIExpression()
!24 = !DILocation(line: 2, column: 13, scope: !4)
!25 = !DILocalVariable(name: "j", arg: 2, scope: !4, file: !1, line: 2, type: !7)
!26 = !DILocation(line: 2, column: 20, scope: !4)
!27 = !DILocation(line: 4, column: 9, scope: !4)
!28 = !DILocation(line: 4, column: 13, scope: !4)
!29 = !DILocation(line: 4, column: 11, scope: !4)
!30 = !DILocation(line: 4, column: 2, scope: !4)
!31 = !DILocalVariable(name: "i", arg: 1, scope: !8, file: !1, line: 6, type: !7)
!32 = !DILocation(line: 6, column: 13, scope: !8)
!33 = !DILocalVariable(name: "j", arg: 2, scope: !8, file: !1, line: 6, type: !7)
!34 = !DILocation(line: 6, column: 20, scope: !8)
!35 = !DILocation(line: 8, column: 9, scope: !8)
!36 = !DILocation(line: 8, column: 11, scope: !8)
!37 = !DILocation(line: 8, column: 10, scope: !8)
!38 = !DILocation(line: 8, column: 2, scope: !8)
!39 = !DILocalVariable(name: "i", arg: 1, scope: !9, file: !1, line: 10, type: !7)
!40 = !DILocation(line: 10, column: 14, scope: !9)
!41 = !DILocation(line: 12, column: 9, scope: !9)
!42 = !DILocation(line: 12, column: 11, scope: !9)
!43 = !DILocation(line: 12, column: 2, scope: !9)
!44 = !DILocalVariable(name: "i", arg: 1, scope: !12, file: !1, line: 14, type: !15)
!45 = !DILocation(line: 14, column: 20, scope: !12)
!46 = !DILocation(line: 16, column: 9, scope: !12)
!47 = !DILocation(line: 16, column: 11, scope: !12)
!48 = !DILocation(line: 16, column: 2, scope: !12)
!49 = !DILocalVariable(name: "a", scope: !16, file: !1, line: 20, type: !7)
!50 = !DILocation(line: 20, column: 6, scope: !16)
!51 = !DILocalVariable(name: "b", scope: !16, file: !1, line: 21, type: !7)
!52 = !DILocation(line: 21, column: 6, scope: !16)
!53 = !DILocalVariable(name: "i", scope: !16, file: !1, line: 22, type: !7)
!54 = !DILocation(line: 22, column: 6, scope: !16)
!55 = !DILocation(line: 22, column: 14, scope: !16)
!56 = !DILocation(line: 22, column: 17, scope: !16)
!57 = !DILocation(line: 22, column: 10, scope: !16)
!58 = !DILocalVariable(name: "j", scope: !16, file: !1, line: 23, type: !7)
!59 = !DILocation(line: 23, column: 6, scope: !16)
!60 = !DILocation(line: 23, column: 14, scope: !16)
!61 = !DILocation(line: 23, column: 17, scope: !16)
!62 = !DILocation(line: 23, column: 10, scope: !16)
!63 = !DILocalVariable(name: "k", scope: !16, file: !1, line: 24, type: !15)
!64 = !DILocation(line: 24, column: 9, scope: !16)
!65 = !DILocation(line: 25, column: 5, scope: !66)
!66 = distinct !DILexicalBlock(scope: !16, file: !1, line: 25, column: 5)
!67 = !DILocation(line: 25, column: 9, scope: !66)
!68 = !DILocation(line: 25, column: 7, scope: !66)
!69 = !DILocation(line: 25, column: 11, scope: !66)
!70 = !DILocation(line: 25, column: 5, scope: !16)
!71 = !DILocation(line: 27, column: 6, scope: !72)
!72 = distinct !DILexicalBlock(scope: !73, file: !1, line: 27, column: 6)
!73 = distinct !DILexicalBlock(scope: !66, file: !1, line: 26, column: 2)
!74 = !DILocation(line: 27, column: 15, scope: !72)
!75 = !DILocation(line: 27, column: 19, scope: !72)
!76 = !DILocation(line: 27, column: 17, scope: !72)
!77 = !DILocation(line: 27, column: 23, scope: !72)
!78 = !DILocation(line: 27, column: 21, scope: !72)
!79 = !DILocation(line: 27, column: 10, scope: !72)
!80 = !DILocation(line: 27, column: 8, scope: !72)
!81 = !DILocation(line: 27, column: 28, scope: !72)
!82 = !DILocation(line: 27, column: 26, scope: !72)
!83 = !DILocation(line: 27, column: 6, scope: !73)
!84 = !DILocation(line: 28, column: 30, scope: !72)
!85 = !DILocation(line: 28, column: 33, scope: !72)
!86 = !DILocation(line: 28, column: 4, scope: !72)
!87 = !DILocation(line: 29, column: 8, scope: !73)
!88 = !DILocation(line: 29, column: 3, scope: !73)
!89 = !DILocation(line: 31, column: 2, scope: !73)
!90 = !DILocation(line: 34, column: 30, scope: !91)
!91 = distinct !DILexicalBlock(scope: !66, file: !1, line: 33, column: 2)
!92 = !DILocation(line: 34, column: 33, scope: !91)
!93 = !DILocation(line: 34, column: 3, scope: !91)
!94 = !DILocation(line: 38, column: 2, scope: !16)
