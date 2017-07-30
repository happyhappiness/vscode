; ModuleID = '/data/download/cmake/cmake-master/Tests/RunCMake/pseudo_emulator_custom_command.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@.str = private unnamed_addr constant [34 x i8] c"generated_exe_emulator_unexpected\00", align 1
@.str.1 = private unnamed_addr constant [33 x i8] c"/generated_exe_emulator_expected\00", align 1
@stderr = external global %struct._IO_FILE*, align 8
@.str.2 = private unnamed_addr constant [36 x i8] c"Failed to find string '%s' in '%s'\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 !dbg !4 {
entry:
  %retval = alloca i32, align 4
  %argc.addr = alloca i32, align 4
  %argv.addr = alloca i8**, align 8
  %substring_failure = alloca i8*, align 8
  %substring_success = alloca i8*, align 8
  %str = alloca i8*, align 8
  store i32 0, i32* %retval, align 4
  store i32 %argc, i32* %argc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %argc.addr, metadata !15, metadata !16), !dbg !17
  store i8** %argv, i8*** %argv.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %argv.addr, metadata !18, metadata !16), !dbg !19
  call void @llvm.dbg.declare(metadata i8** %substring_failure, metadata !20, metadata !16), !dbg !21
  store i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str, i32 0, i32 0), i8** %substring_failure, align 8, !dbg !21
  call void @llvm.dbg.declare(metadata i8** %substring_success, metadata !22, metadata !16), !dbg !23
  store i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.1, i32 0, i32 0), i8** %substring_success, align 8, !dbg !23
  call void @llvm.dbg.declare(metadata i8** %str, metadata !24, metadata !16), !dbg !25
  %0 = load i8**, i8*** %argv.addr, align 8, !dbg !26
  %arrayidx = getelementptr inbounds i8*, i8** %0, i64 1, !dbg !26
  %1 = load i8*, i8** %arrayidx, align 8, !dbg !26
  store i8* %1, i8** %str, align 8, !dbg !25
  %2 = load i32, i32* %argc.addr, align 4, !dbg !27
  %cmp = icmp slt i32 %2, 2, !dbg !29
  br i1 %cmp, label %if.then, label %if.end, !dbg !30

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !31
  br label %return, !dbg !31

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %str, align 8, !dbg !33
  %4 = load i8*, i8** %substring_success, align 8, !dbg !35
  %call = call i8* @strstr(i8* %3, i8* %4) #4, !dbg !36
  %cmp1 = icmp ne i8* %call, null, !dbg !37
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !38

if.then2:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !39
  br label %return, !dbg !39

if.end3:                                          ; preds = %if.end
  %5 = load i8*, i8** %str, align 8, !dbg !41
  %6 = load i8*, i8** %substring_failure, align 8, !dbg !43
  %call4 = call i8* @strstr(i8* %5, i8* %6) #4, !dbg !44
  %cmp5 = icmp ne i8* %call4, null, !dbg !45
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !46

if.then6:                                         ; preds = %if.end3
  store i32 1, i32* %retval, align 4, !dbg !47
  br label %return, !dbg !47

if.end7:                                          ; preds = %if.end3
  %7 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !49
  %8 = load i8*, i8** %substring_success, align 8, !dbg !50
  %9 = load i8*, i8** %str, align 8, !dbg !51
  %call8 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %7, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.2, i32 0, i32 0), i8* %8, i8* %9), !dbg !52
  store i32 1, i32* %retval, align 4, !dbg !53
  br label %return, !dbg !53

return:                                           ; preds = %if.end7, %if.then6, %if.then2, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !54
  ret i32 %10, !dbg !54
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readonly
declare i8* @strstr(i8*, i8*) #2

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!12, !13}
!llvm.ident = !{!14}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Tests/RunCMake/pseudo_emulator_custom_command.c", directory: "/data/download/cmake/cmake-master/Tests/RunCMake")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 14, type: !5, isLocal: false, isDefinition: true, scopeLine: 15, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !7, !8}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !11)
!11 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!12 = !{i32 2, !"Dwarf Version", i32 4}
!13 = !{i32 2, !"Debug Info Version", i32 3}
!14 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!15 = !DILocalVariable(name: "argc", arg: 1, scope: !4, file: !1, line: 14, type: !7)
!16 = !DIExpression()
!17 = !DILocation(line: 14, column: 14, scope: !4)
!18 = !DILocalVariable(name: "argv", arg: 2, scope: !4, file: !1, line: 14, type: !8)
!19 = !DILocation(line: 14, column: 32, scope: !4)
!20 = !DILocalVariable(name: "substring_failure", scope: !4, file: !1, line: 16, type: !9)
!21 = !DILocation(line: 16, column: 15, scope: !4)
!22 = !DILocalVariable(name: "substring_success", scope: !4, file: !1, line: 18, type: !9)
!23 = !DILocation(line: 18, column: 15, scope: !4)
!24 = !DILocalVariable(name: "str", scope: !4, file: !1, line: 19, type: !9)
!25 = !DILocation(line: 19, column: 15, scope: !4)
!26 = !DILocation(line: 19, column: 21, scope: !4)
!27 = !DILocation(line: 20, column: 7, scope: !28)
!28 = distinct !DILexicalBlock(scope: !4, file: !1, line: 20, column: 7)
!29 = !DILocation(line: 20, column: 12, scope: !28)
!30 = !DILocation(line: 20, column: 7, scope: !4)
!31 = !DILocation(line: 21, column: 5, scope: !32)
!32 = distinct !DILexicalBlock(scope: !28, file: !1, line: 20, column: 17)
!33 = !DILocation(line: 23, column: 14, scope: !34)
!34 = distinct !DILexicalBlock(scope: !4, file: !1, line: 23, column: 7)
!35 = !DILocation(line: 23, column: 19, scope: !34)
!36 = !DILocation(line: 23, column: 7, scope: !34)
!37 = !DILocation(line: 23, column: 38, scope: !34)
!38 = !DILocation(line: 23, column: 7, scope: !4)
!39 = !DILocation(line: 24, column: 5, scope: !40)
!40 = distinct !DILexicalBlock(scope: !34, file: !1, line: 23, column: 44)
!41 = !DILocation(line: 26, column: 14, scope: !42)
!42 = distinct !DILexicalBlock(scope: !4, file: !1, line: 26, column: 7)
!43 = !DILocation(line: 26, column: 19, scope: !42)
!44 = !DILocation(line: 26, column: 7, scope: !42)
!45 = !DILocation(line: 26, column: 38, scope: !42)
!46 = !DILocation(line: 26, column: 7, scope: !4)
!47 = !DILocation(line: 27, column: 5, scope: !48)
!48 = distinct !DILexicalBlock(scope: !42, file: !1, line: 26, column: 44)
!49 = !DILocation(line: 29, column: 11, scope: !4)
!50 = !DILocation(line: 29, column: 59, scope: !4)
!51 = !DILocation(line: 30, column: 11, scope: !4)
!52 = !DILocation(line: 29, column: 3, scope: !4)
!53 = !DILocation(line: 31, column: 3, scope: !4)
!54 = !DILocation(line: 32, column: 1, scope: !4)
